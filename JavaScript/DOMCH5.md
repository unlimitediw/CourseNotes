* Graceful degration, ensuring web pages still work with JS.
* Unobtrusive Javascript: separating structure from behaviour.
* Backward compatibility: ensuring that older browsers don't choke on scripts.
* Performance considerations: making sure that your script is performing at its best.

> Graceful degration


* Reference in HTML: <a href="http://www.example.com/" onclick="popUp(this.href);return false;">Example</a>
* Function in JS:

`function popUp(winURL){
  window.open(winURL,"popup","width=320,height=480");
}`
