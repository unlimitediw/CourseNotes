
> Document

* take Documents

> Object

* User-defined objects
* Native objects
* Host object provided by browser

> Model

* A model, like a map is a representation of something.
  * Convention: represent documents as a tree
  
> Node

* A documemnt is a collection of nodes
* ELement nodes: elements such as `<body>`, `<p>` and `<ul>` are the basic building blocks of documents on the web.
* Text nodes: in XHTML, text nodes are always enclosed within elment nodes as content.
* Attribute nodes: Attributes are used to give more specific information about an element. e.g - `<p title="a gentle reminder>...</p>`

> Cascading Style Sheets

* it should be declared in `<head>` with `<style>`.
* e.g `<style>body{color:white;background-color:black;}</style>`
* The class attribute: it can be applied as often and many different elements as you like. "." is the syntax for class, you can also add "h1", "h2" or sth else ahead to specify the area.
#
    <style>.special{color:green;font-style:italic;}</style>
    ...
    <li class="special">Bean</li>

* The ID attribute: it can be used `once` in a web page to uniquely identify an element.
#
    <style>#purchases{border:1px solid white;background-color:#333;color:#ccc;padding:1em;}</style>
    ...
    <ul id="purchases">...</ul>
