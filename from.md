Content-Type: text/x-zim-wiki
Wiki-Format: zim 0.4
Creation-Date: 2013-11-25T17:50:10-08:00

# Ruby on Rails
Created Monday 25 November 2013

To install:
http://gorails.com/setup/ubuntu/13.10

### Creating the website
**1)** *rails nw <webssiteName>	*
	* This will take a little bit to complete the bundle process.
**2)** *railssserver*
	* This starts the localhost server that will run your website.	
**3)** *rails geerate  controller welcome index*
	* Generates controller and HTML page for the website
	* Also adds CSS pages, how exciting!
**4)** *cd app/iews/weelcome*
	index.html.erb -> File to edit
**5)** *cd <webiteDir>>/config*
	* We need to tell the website to go to our index.html.erb	
**6)** *vim routes.rb*
**7)** Uncomment line 7 - *rootwelcome#inndex*

#### To install Bootstrap:
*vim emmFile*
	* Insert *gem 'witter-boootstrap-rails', '~> 2.2.8'*
*bundle install*
*railssserver*


