include make.make

DIRS = src
TESTDIRS = gtest
BUILDDIRS = $(DIRS:%=build-%)
CLEANDIRS = $(DIRS:%=clean-%) $(TESTDIRS:%=clean-%)


all: $(BUILDDIRS)
$(DIRS): $(BUILDDIRS)
$(BUILDDIRS):
	$(MAKE) -C $(@:build-%=%)

test: $(BUILDDIRS) $(TESTDIRS)
$(BUILDDIRS):
	$(MAKE) -C $(@:build-%=%)
$(TESTDIRS): 
	$(MAKE) -C $(@:test-%=%)
	$(MAKE) -C $(@:test-%=%) test

clean: $(CLEANDIRS)
$(CLEANDIRS): 
	$(MAKE) -C $(@:clean-%=%) clean


.PHONY: subdirs $(DIRS)
.PHONY: subdirs $(BUILDDIRS)
.PHONY: subdirs $(TESTDIRS)
.PHONY: subdirs $(CLEANDIRS)
.PHONY: all clean test
