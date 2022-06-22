import * as ReactDOMClient from "react-dom/client";
import { element } from "./Canvas.js";

const root=ReactDOMClient.createRoot(document.getElementById("root"));
root.render(element);