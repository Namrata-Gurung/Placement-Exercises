#<Placement-Exercises>

## Description
This repository contains the changed source code files to placement-exercises. It also includes additional files neccessary for the program to run.


## C++ Calculator Task 
IDE used: Visual Studio Community Version 2022 for Windows

What I did:
- 


How to compile and run the software:


Resources used in C++ Programming task:
- https://www.programiz.com/cpp-programming/examples/calculator-switch-case 
- https://stackoverflow.com/questions/4745311/c-division-by-0 
- https://www.programmingcube.com/write-a-c-program-to-make-a-simple-calculator/ 


## Web API Parsing
IDE used: Visual Studio Code for Mac

What I did:
- Firstly I installed Node.js and npm to write in javascript(node). I checked that it was installed by running commands, 'node --version' and 'npm --version'. Then I installed the HTTP client Axios via the visual studio terminal with , 'npm install axios'. Package.json is included for the axios dependency. 

Explanation of the script:
- Started with a GET request to the URL to dowload contents of the URL.
- Extracted JSON data by storing JSON data in the 'data' variable. Used the assumption that the dtaa contains an array of packs.
- Extracted genres, iterating over each pack to then link the packs to the allGenres array.
- The allGenres array is then sorted into a set so duplicates are removed, which is converted back and sorted in alphabetical order.
- The list of all genres is printed by the console.log() method.
- Then filtered throught the packs to find all packs that include the genre hip-hop, which is printed by the console.log() method.
- In the event of an error, for example the URL cannot be accessed, or a method fails, an error message is produced.


How to compile and run the software:
- To compile ampify.js, Node.js and npm will have to be installed.
- To access the Axios HTTP client, input 'npm install axios' in the terminal which should install the dependencies package.json.
- To run the script, enter 'node.ampify.js' in the terminal. This should give the output of: a list of all the genres and list of packs in the genre hip-hop.

Resources used:
https://code.visualstudio.com/docs/nodejs/nodejs-tutorial
https://nodejs.org/en
https://stackoverflow.com/questions/55374755/node-js-axios-download-file-stream-and-writefile
https://bobbyhadz.com/blog/download-file-using-axios
https://medium.com/@41x3n/scraping-a-website-and-downloading-files-with-node-js-using-axios-and-cheerio-7bbb003f6064

