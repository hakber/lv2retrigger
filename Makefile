BUNDLE = retrigger.lv2
INSTALL_DIR = /usr/local/lib/lv2


$(BUNDLE): manifest.ttl retrigger.ttl retrigger.so
	rm -rf $(BUNDLE)
	mkdir $(BUNDLE)
	cp manifest.ttl retrigger.ttl retrigger.so $(BUNDLE)

retrigger.so: retrigger.cpp
	g++ -shared -fPIC -DPIC retrigger.cpp `pkg-config --cflags --libs lv2-plugin` -o retrigger.so

install: $(BUNDLE)
	mkdir -p $(INSTALL_DIR)
	rm -rf $(INSTALL_DIR)/$(BUNDLE)
	cp -R $(BUNDLE) $(INSTALL_DIR)

clean:
	rm -rf $(BUNDLE) retrigger.so