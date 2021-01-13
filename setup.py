import setuptools

rle_fast_extension = setuptools.Extension("rle.rle_fast",
      sources = ["rle_fast/rle_fast_extension.c"] )

with open('README.md', "r") as f:
    long_description = f.read()

setuptools.setup(
    name='python-rle',
    version="0.0.3",
    author="Tan Nian Wei",
    author_email="tannianwei@aggienetwork.com",
    description="Run-length encoding for data analysis in Python",
    ext_modules = [rle_fast_extension],
    long_description=long_description,
    long_description_content_type="text/markdown",
    url="https://github.com/tnwei/python-rle",
    packages=setuptools.find_packages(),
    install_requires=[
          "tqdm",
      ],
    classifiers=[
        "Programming Language :: Python :: 3",
        "License :: OSI Approved :: MIT License",
        "Operating System :: OS Independent",
    ],
    python_requires='>=3.5',
)
