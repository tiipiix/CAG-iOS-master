//
//  gl_intensitypolygon1textureprogram.vsh
//  Quake-iOS
//
//  Created by Heriberto Delgado on 6/19/16.
//
//TPX: "intensity" is now a vec4 RGBA, and store light color from .lit support

/*
attribute vec3 position;
attribute vec4 intensity;
attribute vec2 texcoords;

varying vec2 texcoords_fragment;
varying vec4 color_fragment;

uniform mat4 transform;

invariant gl_Position;

void main()
{
    gl_Position = transform * vec4(position, 1.0);
    
    texcoords_fragment = texcoords;
    
    color_fragment = intensity;
}
*/

attribute vec3 position;
attribute vec4 intensity;
attribute vec2 texcoords;
attribute vec3 normal;
//attribute vec3 viewpos;
//attribute vec3 lightpos;

varying vec2 texcoords_fragment;
varying vec4 color_fragment;
varying vec3 normal_fragment;

uniform mat4 transform;

invariant gl_Position;

void main()
{
    gl_Position = transform * vec4(position, 1.0);
    
    normal_fragment = normal;
    
    texcoords_fragment = texcoords;
    
    color_fragment = intensity;
}
