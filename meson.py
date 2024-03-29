#!/usr/bin/env python3
import os, sys, shutil

for i in ("shaders", "textures", "fonts"):
    shutil.copytree(
        os.path.join(os.getenv('MESON_SOURCE_ROOT'), "res", i),
        os.path.join(os.getenv('MESON_BUILD_ROOT'), i),
        dirs_exist_ok=True)