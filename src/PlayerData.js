import Constant from "./constants.js"

console.log(Constant.HEIGHT);
export const player={
    'name':"RITESH",
    'color':'green',
    'position':{
        'x':0,
        'y':0
    },
    'dimension':{
    'width':100,
    'height':100
    }
}


export const enemy={
    'name':"Enemy",
    'color':'red',
    'position':{
        'x':Constant.WIDTH-100,
        'y':Constant.HEIGHT-100
    },
    'dimension':{
    'width':100,
    'height':100
    }
}

