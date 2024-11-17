#!/bin/bash

# Run Flake8
echo "Running Flake8..."
flake8 ./ --exclude tests,migrations,venv

# Run Black
echo "Running Black..."
black . --exclude 'venv'
