#!/usr/bin/env python
import sys
import gtk
import appindicator
import subprocess
from subprocess import call

ALIENFX="/usr/local/bin/alienfx-cli"

def create_menu(depth, length=5):
    if depth < 1:
	return None
    menu = gtk.Menu()
    group= None
    for i in range(length):
	menuitem = gtk.RadioMenuItem(group, 'item %2d - %d' % (depth, i))
	group = menuitem
	menu.add(menuitem)
	menuitem.show()
	if depth > 1:
	    submenu = create_menu(depth - 1)
	    menuitem.set_submenu(submenu)
    return menu

class AlienfxCliIndicator:
	def __init__(self):
		self.ind = appindicator.Indicator("alienfx-cli-indicator","indicator-messages",appindicator.CATEGORY_APPLICATION_STATUS)
		self.ind.set_status(appindicator.STATUS_ACTIVE)
		self.ind.set_icon("alienware")
		self.menu_setup()
		self.ind.set_menu(self.menu)

	def create_colors_submenu(self, region_index):
		menu = gtk.Menu()
		color_index = 0
		for color in self.colors:
			if color == "":
				continue
			menuitem = gtk.MenuItem(color)			
			menu.add(menuitem)
			menuitem.show()
			menuitem.connect("activate",self.setLight, region_index,color_index);
			color_index+=1
		
		return menu

	def menu_setup(self):
		self.menu = gtk.Menu()
		
		# Regions item
		regions_item = gtk.MenuItem("Regions:")
		regions_item.show()
		self.menu.append(regions_item)

		
		self.regions = self.getRegions()
		
		self.colors = self.getColors()
		region_index = 0
		for region in self.regions:
			if region == "":
				continue
			menuitem = gtk.MenuItem(region)
			menuitem.show()
			submenu = self.create_colors_submenu(region_index)
			menuitem.set_submenu(submenu)
			self.menu.append(menuitem)
			region_index+=1
			
		
		# add quit item
		self.quit_item = gtk.MenuItem("Quit")     
		self.quit_item.connect("activate", self.quit)
		self.quit_item.show()
		self.menu.append(self.quit_item)
        
	def main(self):
		gtk.main()

	def setLight(self, widget, region_index, color_index):
		call([ALIENFX,str(region_index),str(color_index)]);

	def quit(self, widget):
		sys.exit(0)
	
	def getRegions(self):
		proc = subprocess.Popen([ALIENFX,"--regions"], stdout=subprocess.PIPE)
		tmp = proc.stdout.read()
		return tmp.split("\n")
	
	def getColors(self):
		proc = subprocess.Popen([ALIENFX,"--colors"], stdout=subprocess.PIPE)
		tmp = proc.stdout.read()
		return tmp.split("\n")
	
	
		
if __name__ == "__main__":
	indicator = AlienfxCliIndicator()
	indicator.main()
