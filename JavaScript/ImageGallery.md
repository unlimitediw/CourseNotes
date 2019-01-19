* My first gallery
#
    <html lang="en
        <head>
            <meta charset="utf-8" />
            <title>Image Gallery</title>
        </head>
        <body>
            <h1>Snapshots</h1>
            <ul>
            <li>
                <a href="images/kk.jpg" title="unknown cat">Cat</a>
            </li>
            <li>
                <a href="images/LiWentao.png" title="me">Me</a>
            </li>
            <li>
                <a href="images/Lagrangian.png" title="math">Math</a>
            </li>
            </ul>
        </body>
        </html>

* To hold the image in same page and list
  * Put a placeholder image on the same page as the list
  * When the user clicks a link, intercept the default behaviour
  * Replace the place holder image with the image from the link.

* then use js setAttribute

* showPic
#
    function showPic(pic){
        var source = pic.getAttribute("href");
        var placeholder = document.getElementById("placeholder");
        placeholder.setAttribute("src",source);
    }
    
    onclick="showPic(this);return false;" <!-add to each button you want-->

* childNodes: this property give us information about the children of any elment in a document's node tree
  * It return an array of children.
  
* nodeType
  * Element nodes - 1
  * Attribute nodes - 2
  * Text nodes - 3

* Update Version
#
    function showPic(pic){
        var source = pic.getAttribute("href");
        var placeholder = document.getElementById("placeholder");
        placeholder.setAttribute("src",source);
        var text = pic.getAttribute("title");
        var description = document.getElementById("description");
        description.firstChild.nodeValue = text;
    }


