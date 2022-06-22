const WIDTH=1056;
const HEIGHT=576;

const Canvas = (props) => {
  return (
    <canvas id={props.id} width={props.width} height={props.height}></canvas>
  );
}



const element=<Canvas id="rit" width={WIDTH} height={HEIGHT}/>;

export {element}