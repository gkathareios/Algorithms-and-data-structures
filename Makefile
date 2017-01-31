all: 
	cd ./algorithms && $(MAKE) all
	cd ./data-structures && $(MAKE) all

clean:
	cd ./algorithms && $(MAKE) clean
	cd ./data-structures && $(MAKE) clean