TEMPLATE = subdirs

################################################################################

SUBDIRS += \
    mcutils \
    tests

################################################################################

mcutils.subdir = mcutils
tests.subdir   = tests

tests.depends = mcutils
