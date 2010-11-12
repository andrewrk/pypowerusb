from distutils.core import setup, Extension
import os

def absolute(relative_path):
    "make a relative path absolute"
    return os.path.normpath(os.path.join(os.path.dirname(__file__), relative_path))

powerusb_extension = Extension(
    'powerusb',
    sources = [
        'powerusbmodule.c',
    ],
    include_dirs = [
        absolute('lib'),
    ],
    library_dirs = [
        absolute('lib'),
    ],
    libraries = [
        'PwrUSBDll',
    ],
)

setup(
    name='powerusb',
    version='0.2',
    author="Andrew Kelley",
    author_email="superjoe30@gmail.com",
    url="http://github.com/superjoe30/pypowerusb",
    description='Python library to control PowerUSB',
    license="LGPL",
    ext_modules=[powerusb_extension],
)
