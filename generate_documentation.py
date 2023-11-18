#!/usr/bin/env python3

################################################################################

import subprocess
import clean

################################################################################

if __name__ == "__main__":
    clean.removeDocumentation()
    subprocess.run("doxygen Doxyfile", shell=True)
