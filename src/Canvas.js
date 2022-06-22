const Canvas = (props) => {
  return (
    <canvas width={props.width} height={props.height}></canvas>
  );
}

const element=<Canvas width="576" height="576"/>;

export {element}