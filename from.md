Content-Type: text/x-zim-wiki  
Wiki-Format: zim 0.4  
Creation-Date: 2013-11-25T17:50:10-08:00  
  
# Ruby on Rails  
Created Monday 25 November 2013  
  
To install:  
http://gorails.com/setup/ubuntu/13.10  
  
### Creating the website  
**1)**  *rails new <websiteName>*	   
	* This will take a little bit to complete the bundle process.  
**2)** *rails server*  
	* This starts the localhost server that will run your website.	  
**3)** *rails generate controller welcome index*  
	* Generates controller and HTML page for the website  
	* Also adds CSS pages, how exciting!  
**4)** *cd app/views/welcome*  
	index.html.erb -> File to edit  
**5)** *cd <websiteDir>/config*  
	* We need to tell the website to go to our index.html.erb	  
**6)** *vim routes.rb*  
**7)** Uncomment line 7 - *root welcome#index*  
  
#### To install Bootstrap:  
*vim GemFile*  
	* Insert *gem 'twitter-bootstrap-rails', '~> 2.2.8'*  
*bundle install*  
*rails server*  
![alt text](~/Pictures/Screenshot from 2014-03-09 16:59:02.png "Title Text")  
  
