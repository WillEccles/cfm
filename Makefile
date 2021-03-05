SDIR = src
BDIR = build

TARGET = cfm
SRC = $(wildcard $(SDIR)/*.cpp)
OBJ = $(patsubst $(SDIR)/%.cpp,$(BDIR)/%.o,$(SRC))
DEP = $(addsuffix .d,$(OBJ))
CONF = config.h
DEFCONF = config.def.h
MANPAGE = cfm.1
PREFIX ?= /usr/local

CXXFLAGS += -O3 -std=c++17 -Wall -W -pedantic
CPPFLAGS += -D_XOPEN_SOURCE=700
LDFLAGS += -s -flto -fwhole-program

.PHONY: all install uninstall clean

all: $(TARGET)

$(TARGET): $(OBJ)
	@echo "linking $@"
	@$(CXX) $(CXXFLAGS) $(LDFLAGS) $(OBJ) -o $@

-include $(DEP)

$(BDIR)/%.o: $(SDIR)/%.cpp | $(BDIR)
	@echo "$@"
	@$(CXX) $(CXXFLAGS) $(CPPFLAGS) -MMD -MP -o $@ -c $<

$(CONF):
	@cp -v $(DEFCONF) $(CONF)

$(BDIR):
	mkdir -p $(BDIR)

install: $(TARGET)
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	mkdir -p $(DESTDIR)$(PREFIX)/share/man/man1
	install -m755 $(TARGET) $(DESTDIR)$(PREFIX)/bin/$(TARGET)
	install -m644 $(MANPAGE) $(DESTDIR)$(PREFIX)/share/man/man1/$(MANPAGE)

uninstall:
	$(RM) $(DESTDIR)$(PREFIX)/bin/$(TARGET)
	$(RM) $(DESTDIR)$(PREFIX)/share/man/man1/$(MANPAGE)

clean:
	$(RM) -r $(BDIR)
	$(RM) $(TARGET)
