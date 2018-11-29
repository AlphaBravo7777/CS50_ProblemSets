[Problem Set 6: Web Server](http://cdn.cs50.net/2015/fall/psets/6/pset6/pset6.html)
===


Run code from port 8080:

    ./server /home/ubuntu/workspace/pset6/public/


During debugging the listening port is not always free, and for the next start of the server it is necessary to kill all processes associated with this port using the command:

    killall -9 server


Run staff version:

    ~ cs50 / pset6 / server public

With its help, you can compare server responses to certain requests with those issued by your option. You can do this by clicking on the links of your web page, which is hosted at https://ide50-username.cs50.io (username is the nickname you registered at https://cs50.io), or by writing requests in the browser address bar, or using the curl utility in a separate terminal. Typing for example

    curl -i http: // localhost: 8080 / cat.html
    
, you kind of request the cat.html page, and if your server is working properly, it will issue an HTTP / 1.1 200 OK response, and curl will output the contents of the resulting web page.
