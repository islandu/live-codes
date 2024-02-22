#!/usr/bin/python3

from setuptools import setup, Extension
# from setuptools import dist, Distribution
# from setuptools import build_meta

# command to run for build
# python3 -m build --sdist --outdir build

# class MyDistribution(Distribution):
#     def get_egg_cache_dir(self) -> str:
#         return super().get_egg_cache_dir()

_module_name = 'fib64py'
_module_src = [
    f'src/{_module_name}.c',
    'src/fib64userops.c'
]
_include = ['include']


setup(
    name=_module_name,
    version='0.1',
    ext_modules=[
        Extension(
            _module_name,
            sources=_module_src,
            include_dirs=_include
        )
    ]
)
