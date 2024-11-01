#!/bin/bash

# Run Flake8
echo "Running Flake8..."
flake8 python

# Run Black
echo "Running Black..."
black --check python
