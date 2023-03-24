#!/usr/bin/python3
import os, sys, shutil

try:
    for i in ("shaders", "textures"):
        shutil.rmtree(
            os.path.join(os.getenv('MESON_BUILD_ROOT'), i))
        shutil.copytree(
            os.path.join(os.getenv('MESON_SOURCE_ROOT'), "res", i),
            os.path.join(os.getenv('MESON_BUILD_ROOT'), i))
except FileExistsError:
    exit(0)