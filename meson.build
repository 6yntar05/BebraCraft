project('BebraCraft', 'cpp')
src_dir = 'src'

warning_args = ['-Wall', '-Wextra', '-Wpedantic', '-Wno-unused-parameter']

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

    link_args: [
        '-lGL',
        '-lGLEW',
        '-lSDL2',
    ],

    c_args: warning_args + [
        '-fdiagnostics-color=always',
        '-O3',
    ],
    cpp_args: warning_args + [
        '-fdiagnostics-color=always',
        '-O3',
        '-std=c++20'
    ]
)

run_command(find_program('meson.py'), check: true)