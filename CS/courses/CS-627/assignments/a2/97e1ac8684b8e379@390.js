function _1(md){return(
md`# Nate Warner CS-490N9 assignment 2`
)}

function _2(htl){return(
htl.html`<div id="info">
  <div class="left">
    <h1 class="left-text">Nate Warner</h1>
    <h2 class="left-text">z2004109</h2>
  </div>
  <div class="right">
    <h2 class="right-text">Data visualization (CSCI 627/490 Section N9)</h2>
    <h2 class="right-text">01/28/2026</h2>
  </div>
</div>
<style>
  * { margin: 0; }

  #info { display: flex }

  .left {
    margin: 1%;
    display: flex;
    width: 70%;
    flex-direction: column;
  }
  .left .left-text { color: blue; }

  .right {
    margin: 1%;
    display: flex;
    flex-direction: column;
    width: 30%;
    border: 3px solid green;
  }
  .right .right-text {
    text-align: right;
    margin-right: 10px;
    color: blue;
    font-style: italic;
    font-weight: normal;
  }
</style>`
)}

async function _3(d3)
{
window.data = await d3.csv("https://gist.githubusercontent.com/dakoop/a191fdcc9603800ded912786047fd998/raw/df97c4648967e46e268f01bdd20e661c4bf6884b/newspaper-circulation.csv", d3.autoType);
  return window.data;
}


function _process_data(){return(
function process_data(data) {
  let proc = data.filter((v, i, a) => v.Year != 1940 && v.Year != 2010)
                  .map((v,i,a) => ({
                               Year: +v.Year, 
                               Weekday: +v.Weekday + +v.WeekdayEst, 
                               Sunday: +v.Sunday + +v.SundayEst, 
                               Average: ((+v.Weekday + +v.WeekdayEst) + (+v.Sunday + +v.SundayEst)) / 2
                             }));
  
  return proc;
}
)}

function _5(process_data,html)
{
let processed_data = process_data(window.data);
return html`
<table>
  <tr>
    <th> Year </th>
    <th> Weekday </th>
    <th> Sunday </th>
    <th> Average </th>
  </tr>
  ${processed_data.map((v,i,a) => html`
      <tr>
      <td> <b> ${v.Year} <b> </td>
      <td> ${v.Weekday}</td>
      <td> ${v.Sunday} </td>
      <td> ${v.Average} </td>
     </tr>
    `
  )}
</table>
`
}


function _6(process_data)
{
let data = process_data(window.data);  

// Set width and height variables
const W = 400, H = 600;

// Set margin object
const margins = {left: 40, right: 0, top: 12, bottom: -25};

// Find number of bar
const k = data.reduce(acc => acc+1, 0);

// Get height of each bar 
const barHeight = ((H-33)/k);

// Find min and max years in data
const maxYear = Math.max(...data.map(d => d.Year));
const minYear = Math.min(...data.map(d => d.Year));

// Find max average in data
const maxAverage = Math.max(...data.map(d => d.Average));

// Create root node (svg)
const svg = document.createElementNS("http://www.w3.org/2000/svg", "svg");

// Set properties of svg node
svg.setAttribute("width", W);
svg.setAttribute("height", H);

// Create x axis
const xAxis = document.createElementNS("http://www.w3.org/2000/svg", "line");
xAxis.setAttribute("x1", 0+margins.left);
xAxis.setAttribute("y1", H+margins.bottom);
xAxis.setAttribute("x2", W+margins.right);
xAxis.setAttribute("y2", H+margins.bottom);
xAxis.setAttribute("stroke", "black");
xAxis.setAttribute("stroke-width", 2);
svg.appendChild(xAxis);

// Create y axis
const yAxis = document.createElementNS("http://www.w3.org/2000/svg", "line");
yAxis.setAttribute("x1", 0+margins.left);
yAxis.setAttribute("y1", 0);
yAxis.setAttribute("x2", 0+margins.left);
yAxis.setAttribute("y2", H+margins.bottom);
yAxis.setAttribute("stroke", "black");
yAxis.setAttribute("stroke-width", 2);
svg.appendChild(yAxis);

// x range
const xMin = document.createElementNS("http://www.w3.org/2000/svg", "text");
xMin.setAttribute("x", 0+margins.left);
xMin.setAttribute("y", H);
xMin.appendChild(document.createTextNode(0));
svg.appendChild(xMin);

// x range
const xMax = document.createElementNS("http://www.w3.org/2000/svg", "text");
xMax.setAttribute("x", W-90);
xMax.setAttribute("y", H);
xMax.appendChild(document.createTextNode(Math.round(maxAverage / 1e6) * 1e6 + 1e6));
svg.appendChild(xMax);

// y range
const yMin = document.createElementNS("http://www.w3.org/2000/svg", "text");
yMin.setAttribute("x", 0);
yMin.setAttribute("y", 0+margins.top);
yMin.appendChild(document.createTextNode(minYear));
svg.appendChild(yMin);

// y range
const yMax = document.createElementNS("http://www.w3.org/2000/svg", "text");
yMax.setAttribute("x", 0);
yMax.setAttribute("y", H+margins.bottom);
yMax.appendChild(document.createTextNode(maxYear));
svg.appendChild(yMax);

// Display bars on chart
data.forEach((d,i,a) => {
  const bar = document.createElementNS("http://www.w3.org/2000/svg", "rect");
  bar.setAttribute("x", 0+margins.left);
  bar.setAttribute("y", ((d.Year - 1945) * barHeight));
  bar.setAttribute("width", ((W-margins.left)/maxAverage)*(d.Average));
  // Subtracting one from the bar height behaves differently here vs where barHeight is defined
  bar.setAttribute("height", barHeight-1);

  svg.appendChild(bar);
});
  
return svg;
}


function _7(process_data)
{
let data = process_data(window.data);  

// Set width and height variables
const W = 600, H = 400;

// Set margin object
const margins = {left: 80, right: 0, top: 12, bottom: -25};

// Find number of bar
const k = data.reduce(acc => acc+1, 0);

// Get height of each bar 
const barHeight = (((W-margins.left)-33)/k);

// Find min and max years in data
const maxYear = Math.max(...data.map(d => d.Year));
const minYear = Math.min(...data.map(d => d.Year));

// Find max average in data
const maxAverage = Math.max(...data.map(d => d.Average));

// Create root node (svg)
const svg = document.createElementNS("http://www.w3.org/2000/svg", "svg");

// Set properties of svg node
svg.setAttribute("width", W);
svg.setAttribute("height", H);

// Create x axis
const xAxis = document.createElementNS("http://www.w3.org/2000/svg", "line");
xAxis.setAttribute("x1", 0+margins.left);
xAxis.setAttribute("y1", H+margins.bottom);
xAxis.setAttribute("x2", W+margins.right);
xAxis.setAttribute("y2", H+margins.bottom);
xAxis.setAttribute("stroke", "black");
xAxis.setAttribute("stroke-width", 2);
svg.appendChild(xAxis);

// Create y axis
const yAxis = document.createElementNS("http://www.w3.org/2000/svg", "line");
yAxis.setAttribute("x1", 0+margins.left);
yAxis.setAttribute("y1", 0);
yAxis.setAttribute("x2", 0+margins.left);
yAxis.setAttribute("y2", H+margins.bottom);
yAxis.setAttribute("stroke", "black");
yAxis.setAttribute("stroke-width", 2);
svg.appendChild(yAxis);

// x range
const xMin = document.createElementNS("http://www.w3.org/2000/svg", "text");
xMin.setAttribute("x", 0+margins.left);
xMin.setAttribute("y", H);
xMin.appendChild(document.createTextNode(minYear));
svg.appendChild(xMin);

// x range
const xMax = document.createElementNS("http://www.w3.org/2000/svg", "text");
xMax.setAttribute("x", W-35);
xMax.setAttribute("y", H);
xMax.appendChild(document.createTextNode(maxYear));
svg.appendChild(xMax);

// y range
const yMin = document.createElementNS("http://www.w3.org/2000/svg", "text");
yMin.setAttribute("x", 0);
yMin.setAttribute("y", 0+margins.top);
yMin.appendChild(document.createTextNode(Math.round(maxAverage / 1e6) * 1e6 + 1e6));
svg.appendChild(yMin);

// y range
const yMax = document.createElementNS("http://www.w3.org/2000/svg", "text");
yMax.setAttribute("x", margins.left-15);
yMax.setAttribute("y", H+margins.bottom);
yMax.appendChild(document.createTextNode(0));
svg.appendChild(yMax);

// Display bars on chart
data.forEach((d,i,a) => {
  const height = ((H+margins.bottom)/maxAverage)*(d.Average);
  const bar = document.createElementNS("http://www.w3.org/2000/svg", "rect");
  bar.setAttribute("y", H-height+margins.bottom);
  bar.setAttribute("x", (((d.Year - 1945) * barHeight))+margins.left);
  bar.setAttribute("width", barHeight-1);
  bar.setAttribute("height", height);
  
  svg.appendChild(bar);
});
  
return svg;
}


export default function define(runtime, observer) {
  const main = runtime.module();
  main.variable(observer()).define(["md"], _1);
  main.variable(observer()).define(["htl"], _2);
  main.variable(observer()).define(["d3"], _3);
  main.variable(observer("process_data")).define("process_data", _process_data);
  main.variable(observer()).define(["process_data","html"], _5);
  main.variable(observer()).define(["process_data"], _6);
  main.variable(observer()).define(["process_data"], _7);
  return main;
}
