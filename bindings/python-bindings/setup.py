from setuptools import setup
from pyvemu import __version__

setup(
    name='pyvemu',
    version=__version__,
    description="VEMU bindings",
    long_description="VEMU bindings for creating VGA images",
    url="https://github.com/MCausc78/VEMU/tree/master/bindings/python-bindings",
    author="MCausc78",
    author_email="mcausc78@gmail.com",
    license="GPLv3",
    packages=["pyvemu"],
    classifier=[
        'Programming Language :: Python :: 3',
        'Intended Audience :: Developers',
        'License :: GPLv3 License',
        'Topic :: Software Development :: Libraries',
        'Topic :: Utilities',
        'License :: OSI Approved :: GPLv3 License',
        'Operating System :: Independent',
    ],
    keywords="vga vemu bindings vgabindings",
    zip_safe=False,
)