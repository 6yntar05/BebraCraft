project('BebraCraft', 'cpp')
src_dir = 'src'

compiller_args = ['-Wall', '-Wextra', '-Wpedantic', '-Wno-unused-parameter', '-fdiagnostics-color=always']
linker_args = ['-lGL', '-lGLEW', '-lSDL2', '-lSDL2_image']

if get_option('buildtype') == 'debug'
    compiller_args += ['-fsanitize=address', '-O0', '-g']
    linker_args += '-fsanitize=address'
else
    compiller_args += '-O3'
endif

subdir('src') # -> src_files

executable(
    'BebraCraft',
    src_files,

    dependencies: [
        dependency('opengl'),
        dependency('glew'),
        dependency('sdl2'),
    ],

    include_directories: [
        src_dir,
        'res',
    ],

    link_args: linker_args,
    c_args: compiller_args,
    cpp_args: compiller_args + ['-std=c++20']
)

run_command(find_program('meson.py'), check: true)