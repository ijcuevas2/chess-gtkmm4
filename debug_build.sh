#!/bin/bash
cd build
cmake .. && ninja && ./run_tests && ./chess
