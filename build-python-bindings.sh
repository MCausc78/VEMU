#!/bin/bash

cd bindings
cd python-bindings
python3 -m pip install --upgrade build
sudo apt install python3.10-venv -y
python3 -m build