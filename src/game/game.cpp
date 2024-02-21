#include "engine/core.h"
#include "engine/graphics/framebuffer.h"
#include "engine/graphics/shaders.h"
#include "engine/objects/objects.h"
#include "engine/objects/model.h"
#include "engine/objects/base.h"
#include "engine/utils/glerrors.h"
#include "engine/utils/font.h"
#include "engine/camera.h"

#include "game/world/demoChunkGen.h"
#include "game/world/skybox.h"
#include "game/control.h"

#include <exception>
#include <functional>
#include <stdexcept>
#include <typeinfo>
#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <map>
#include <memory>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SDL_log.h>

#ifdef __EMSCRIPTEN__
    #include <emscripten.h>
    #include <emscripten/html5_webgl.h>
    #include <emscripten/wasmfs.h>
#endif

class SystemContextSingleton {
public:
    static SystemContextSingleton& getInstance() {
        static SystemContextSingleton instance;
        return instance;
    }

    void init() {
        bebra::init();
    }

    bebra::Window* createWindow() {
        SDL_DisplayMode display = bebra::getDisplay();
        window_ = new bebra::Window {"BebraCraft", std::move(display), SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE};
        return window_;
    }

    void createRenderContext(const std::bitset<4> flags = {0}) {
        // TODO: Multisample buffer
        #ifdef __EMSCRIPTEN__
            bebra::glContextCreate(*window_, bebra::GApi::WebGL, std::move(flags));
        #else 
            bebra::glContextCreate(*window_, bebra::GApi::OpenGL, std::move(flags));
        #endif
        // -> SDL_GLContext
    }

public:
    bebra::Window* getWindow() {
        return window_;
    }
    
private:
    bebra::Window* window_;
};

class ObjectsManager {};

class ResourceManager {
public:
    bebra::graphics::ScreenObject& getScreen() { return screen; }
    bebra::utils::Font& getFont() { return text; }
    bebra::Window* getWindow() { return window; }
    void setWindow( bebra::Window* window_ ) { window = window_; }

private:
    // Low level resources
    bebra::graphics::ScreenObject screen {640, 480, bebra::graphics::ShaderProgram { "shaders/screen.vert", "shaders/screen.frag" }};
    bebra::utils::Font text {"./fonts/Monocraft.ttf", bebra::graphics::ShaderProgram {"shaders/font.vert", "shaders/font.frag"}, 18};
    bebra::Window* window = nullptr;

    // Managers
    ObjectsManager mObjects_;
};

class Scene { // TODO: Move to engine
public:
    Scene( std::shared_ptr<ResourceManager> mResource ) : mResource(mResource) {}
    virtual void handleInput() = 0; //
    virtual void render() = 0;
    std::shared_ptr<ResourceManager> mResource;

private:
    // std::vector<Object> vObjects;
    // std::vector<Script> vScripts;
    // std::vector<Scene> vScenes;
};

class MenuScene : public Scene {
private:
    bebra::Camera camera;
    std::list<SDL_Keycode> keyPressed;
    
public:
    MenuScene( std::shared_ptr<ResourceManager> mResource )
        : Scene( mResource )
        , camera (glm::vec3(-2.0f, 8.0f, 6.0f), 90, 0.05)
        {}

    void handleInput() override {
        bool isModeChanged = false;
        auto window = mResource->getWindow();
        ::handleInput(keyPressed, camera, *window, isModeChanged);
        if (isModeChanged)
            mResource->getScreen().updateMode(window->mode.w, window->mode.h);
    };

    void render() override {
        auto window = mResource->getWindow();
        glm::mat4 projectionOrtho = glm::ortho(0.0f, float(window->mode.w), 0.0f, float(window->mode.h));
        mResource->getScreen().clear();
        mResource->getFont().render("BebraCraft pre-alpha: " + std::string(__DATE__), projectionOrtho, window->mode.w/2.0 - 200.0, window->mode.h/2.0);
        bebra::utils::glHandleError(glGetError());
    }
};

class GameScene : public Scene {
private:
    // GAME RESOURCES
    bebra::Camera camera;
    craft::skybox skybox;
    bebra::objects::chunk chunk;
    bebra::world::Chunk testCoolChunk;
    uint64_t time;

    std::list<SDL_Keycode> keyPressed;
    float worldTime = 0.0, rawTime = 0.0;
    float maxFrametime = 0.0;
    uint64_t start = SDL_GetPerformanceCounter();

public:
    GameScene( std::shared_ptr<ResourceManager> mResource )
        : Scene( mResource )
        , camera (glm::vec3(-2.0f, 8.0f, 6.0f), 90, 0.05)
        , skybox ( bebra::graphics::ShaderProgram {"shaders/skybox.vert", "shaders/skybox.frag"} )
        , chunk ( craft::genChunk() )
        , testCoolChunk ( &chunk, 0, 0 )
    {}

    void handleInput() override {
        bool isModeChanged = false;
        auto window = mResource->getWindow();
        ::handleInput(keyPressed, camera, *window, isModeChanged);
        if (isModeChanged)
            mResource->getScreen().updateMode(window->mode.w, window->mode.h);
    };

    void render() override {
        unsigned int callsCounter = 0;
        auto window = mResource->getWindow();

            // Loading shaders
        bebra::graphics::ShaderProgram blockShader {"shaders/block.vert", "shaders/block.frag"};
        bebra::graphics::BlockShaderApi blockShaderSet {blockShader};
            // Buffers
        GLuint VBO, plantVAO, fluidVAO, blockVAO, EBO;
        bebra::objects::Plant::loadObject(VBO, plantVAO, EBO);
        bebra::objects::Fluid::loadObject(VBO, fluidVAO, EBO);
        bebra::objects::Block::loadObject(VBO, blockVAO, EBO);

        // Calculate shadertime
        worldTime += 0.001;
        rawTime = 0.5 + (glm::cos(worldTime) / 2.0);

        // Position calculation // Todo: put into a camera class
        glm::mat4 model          = glm::rotate(glm::mat4(1.0f), 1.0f * glm::radians(50.0f), glm::vec3(0.0f, 0.0f, 0.0f));
        glm::mat4 view           = glm::lookAt(camera.pos, camera.pos + camera.front, camera.up);
        glm::mat4 viewIdenpedent = glm::mat4(glm::mat3(view));
        glm::mat4 projection     = glm::perspective(
                                        glm::radians(camera.fov),
                                        float(window->mode.w) / float(window->mode.h),
                                        0.1f, 3000.0f
                                    ); // 3000 - render distance
        glm::mat4 projectionFont = glm::ortho(0.0f, float(window->mode.w), 0.0f, float(window->mode.h));

        glm::vec3 direction;
            direction.x = cos(glm::radians(camera.yaw)) * cos(glm::radians(camera.pitch));
            direction.y = sin(glm::radians(camera.pitch));
            direction.z = sin(glm::radians(camera.yaw)) * cos(glm::radians(camera.pitch));
        camera.front = glm::normalize(direction);

        // Offscreen rendering in G-Buffer // TODO: fix for opengles
        //screen.gbuffer->bind();
        mResource->getScreen().clear();
        skybox.render(viewIdenpedent, projection, rawTime);
        //if (window->debug.lines)
        //    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        { // Chunks rendering
            static std::function chunkPass = [&](bebra::objects::ObjIdent who, int chunkX, int chunkY) {
                blockShader.use();
                blockShaderSet.model(model);
                blockShaderSet.view(view);
                blockShaderSet.projection(projection);
                blockShaderSet.worldTime(rawTime);
                for (int iLayer = 0; iLayer < 15; iLayer++) {
                    bebra::objects::chunkLayer& layer = chunk.at(iLayer);
                    for (int iRow = 0; iRow < 16; iRow++) {
                        bebra::objects::chunkRow& row = layer.at(iRow);
                        for (int iBlock = 0; iBlock < 16; iBlock++) {
                            const bebra::objects::Object* block = row.at(iBlock);
                            
                            // Check for air
                            if (!block->texture.arraySize || block->id == bebra::objects::ebase) continue;

                            //
                            if(!((who == block->id) ||
                                ((who == bebra::objects::etransparent) && (block->id == bebra::objects::eplant)) ||
                                ((who == bebra::objects::esemitransparent) && (block->id == bebra::objects::efluid))
                            )) continue;

                            if (who == bebra::objects::esemitransparent)
                                glDepthMask(GL_FALSE);

                            // Pick right buffers for current object
                            switch(block->id) {
                                case bebra::objects::eplant: { glBindVertexArray(plantVAO); break; }
                                case bebra::objects::efluid: { glBindVertexArray(fluidVAO); break; }
                                default: { glBindVertexArray(blockVAO); break; }
                            }

                            // Block space transformation
                            glm::mat4 model = glm::mat4(1.0f);
                            model = glm::translate(model, { iBlock + chunkX*16, iLayer, iRow + chunkY*16});

                            //if (block->rotate != 0.0)
                            //    model = glm::rotate(model, glm::radians(block->rotate), { 0.0, 1.0, 0.0 });
                            blockShaderSet.model(model);

                            // TODO: texture sets manager
                            GLint textureSlot = GL_TEXTURE0;
                            GLint textureSlotIndex = 0; // < Max texture slots
                            glActiveTexture(textureSlot + textureSlotIndex);
                            glBindTexture(GL_TEXTURE_2D, block->texture.textureArray);
                            //glBindTexture(GL_TEXTURE_2D_ARRAY, block->texture.textureArray);
                            //glUniform1i(glGetUniformLocation(blockShader.program, "textureArray"), (textureSlot-GL_TEXTURE0)+textureSlotIndex);
                            glUniform1i(glGetUniformLocation(blockShader.program, "textureUV"), (textureSlot-GL_TEXTURE0)+textureSlotIndex);
                            if (block->id == bebra::objects::eplant) {
                                glDisable(GL_CULL_FACE);
                                glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
                                glEnable(GL_CULL_FACE);
                            } else {
                                glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
                            }
                            callsCounter++;

                            if (who == bebra::objects::esemitransparent)
                                glDepthMask(GL_TRUE);
                        }
                    }
                }
            };
            
            int x = 0, y = 0;
            //for (int x = 0; x < 8; x++) for (int y = 0; y < 8; y++) // TODO: reduce draw calls
            {
                chunkPass(bebra::objects::esolid, x, y);
                chunkPass(bebra::objects::etransparent, x, y); // Mipmaps turns transparent textures to semitranspaent on some fragments

                //entityShaderSet.program.use();
                //entityShaderSet.model(model);
                //entityShaderSet.view(view);
                //entityShaderSet.projection(projection);
                //entityShaderSet.worldTime(rawTime);
                //gltfModel.render({10 + x*16, 6.5, 4 + y*16}, entityShaderSet);
                //gltfModel.render({}, entityShaderSet);
                
                chunkPass(bebra::objects::esemitransparent, x, y);
                // Mesh test:
                //testCoolChunk.meshSolid.render();
            }

        }

        {// Render from G-Buffer
            //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            //screen.gbuffer->unbind();
            //screen.clear();
            //screen.render(!window->debug.nohud);
        }

        { // Calculate frametime & FPS
            auto end = SDL_GetPerformanceCounter();
            float Frametime = ((end - start) * 1000.0) / (float)SDL_GetPerformanceFrequency();
            if (Frametime > maxFrametime)
                maxFrametime = Frametime;
            else
                maxFrametime = ((maxFrametime * 50.0) + Frametime) / 51.0;
            start = end;

            // Render HUD
            if (!window->debug.nohud) {
                static std::function topOffset =[&](unsigned int lineFromTop) {
                    return 10;
                    //return float(window->mode.h) - ((float(std::max(text.width, text.height)) + 5.0) * (lineFromTop + 1));
                };

                mResource->getFont().render("Frametime: " + std::to_string(Frametime) + "ms" +
                            " / 2%Max: " + std::to_string(maxFrametime) + "ms",
                            projectionFont, 10.0, topOffset(0));
                mResource->getFont().render("Draw calls: " + std::to_string(callsCounter), projectionFont, 10.0, topOffset(1));
                mResource->getFont().render("BebraCraft pre-alpha: " + std::string(__DATE__), projectionFont, 10.0, topOffset(2));
                mResource->getFont().render("Testchunk", projectionFont, 10.0, topOffset(3));
            }
        }

        bebra::utils::glHandleError(glGetError());
    }
};

class SceneManager {
private:
    std::shared_ptr<Scene> currentScene;
    std::shared_ptr<ResourceManager> mResource;

public:
    SceneManager( std::shared_ptr<ResourceManager> mResource ) : mResource(mResource) {}

    void switchScene(std::shared_ptr<Scene> newScene) {
        if ( currentScene == newScene ) return;
        currentScene = std::move(newScene);
    }

    void handleInput() {
        currentScene->handleInput();
        static int i = 0;
        if (i == 200) { // Switch scene
            switchScene(std::make_shared<GameScene>( mResource ));
            ++i;
        } else if ( i < 200 ) ++i;
    }

    void render() { currentScene->render();}

    std::shared_ptr<Scene> getSceneInstance() { return currentScene; }
    std::shared_ptr<ResourceManager> getResourceManager() { return mResource; }
};

static void mainLoop(void* SceneManagerPtr) {
    auto sceneManager = reinterpret_cast<SceneManager*>(SceneManagerPtr);
    sceneManager->handleInput();
    sceneManager->render();
    bebra::utils::glHandleError(glGetError());
    SDL_GL_SwapWindow(sceneManager->getResourceManager()->getWindow()->itself);
#ifdef __EMSCRIPTEN__
    emscripten_webgl_commit_frame();
#endif
}

int main(int argc, char* argv[]) {
    auto systemContext = SystemContextSingleton::getInstance();

    systemContext.init();
    auto window = systemContext.createWindow();
    systemContext.createRenderContext(bebra::AA | bebra::Multisample | bebra::Debug);

    std::shared_ptr<ResourceManager> mResource = std::make_shared<ResourceManager>();
    mResource->setWindow( window );

    SceneManager mScene( mResource );
    mScene.switchScene(std::make_shared<MenuScene>( mResource ));

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop_arg(mainLoop, reinterpret_cast<void*>(&mScene), 0, 1);
#else
    while (window->isRunning)
        mainLoop(&mScene);
#endif

    SDL_Quit();
    return 0;
}