import {Constant} from "./constants.js"

export const player={
    'name':"RITESH",
    'color':'green',
    'velocity':{
        'vx':5,
        'vy':0
    },
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
    'velocity':{
        'vx':-5,
        'vy':0
    },
    'position':{
        'x':Constant.WIDTH-100,
        'y':Constant.HEIGHT-100
    },
    'dimension':{
    'width':100,
    'height':100
    }
}

