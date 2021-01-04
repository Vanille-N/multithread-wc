#!/bin/bash

< /dev/urandom tr -dc '\n\t [:alnum:]' | head -c$1
