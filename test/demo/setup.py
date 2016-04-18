from distutils.core import setup,Extension

example_module = Extension(
    '_example',
    sources = [],
    include_dirs = ['inc'],
    libraries = ['TEService'],
    library_dirs = ['lib/debug'],
    extra_link_args = [],
)

setup(
    name='example',
    version='1.0',
    py_modules=["example"],
    ext_modules=[example_module],
)

