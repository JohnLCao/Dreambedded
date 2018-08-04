# Dreambedded
Project for Embedded Systems using the BeagleBone Green. 

* [High level architecture](https://drive.google.com/file/d/1BDMiIV8yohG4y36VP3uiOJNSGxTPou9D/view) 

* Loosely following this [Code Organization Guide](https://hiltmon.com/blog/2013/07/03/a-simple-c-plus-plus-project-structure/)

* Building for Sensor Wrappers and Monitor <br />
	* Clone this repository. <br />
	* change directory into beaglebone_green <br />
	* run `make` <br />
	* Caveats:  <br />
		* make sure that IR sensor is wired up to BBG's AIN pin 1 <br />
		* make sure that Sound sensor is wired up to BBG's AIN pin 4 <br />
	* Go to BBG's /mnt/remote/myApps directory <br />
	* run `./dreambed` <br />

* Building for Relay(RPI) and node server <br />
	* Clone this repository. <br />
	* change directory into raspberry_pi <br />
	* run `make` <br />
	* Go to RPI's /mnt/remote/myApps/rpi directory <br />
	* run `./dreambed` <br />
	* For the node server
	* Go to /mnt/remote/myApps/rpi/server, run npm intall
	* and then `npm run start`. Off you go.
