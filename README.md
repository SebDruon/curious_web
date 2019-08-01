# curious_web

This app was made as a small example of how to use **webkit2** and **gtk3**.
This is a very basic web browser, with a neat little extra functionality : it will display the url
of any resource loaded by the web page : images, fonts, scripts and so on ...

## Dependencies

- gtk3
- webkit2-gtk-4.0

## Build instructions

- git clone https://github.com/druon/curious_web.git
- cd curious_web
- cd build
- cmake ..
- make
- (as root) make install

## Usage

curious_web https://www.codices.org

Don't forget the http:// or https:// in the url !

