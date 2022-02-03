//
//  gl_intensitypolygon1textureprogram.fsh
//  Quake-iOS
//
//  Created by Heriberto Delgado on 5/14/16.
//
//

/*
uniform sampler2D texture;

varying mediump vec2 texcoords_fragment;
varying mediump vec4 color_fragment;

invariant gl_FragColor;

void main()
{
    gl_FragColor = color_fragment * texture2D(texture, texcoords_fragment);
}
*/

uniform sampler2D texture;

varying mediump vec2 texcoords_fragment;
varying mediump vec4 color_fragment;
varying mediump vec3 normal_fragment;

mediump vec3 normal;

invariant gl_FragColor;

//invariant vec3 norm;

void main()
{
    //vec3 viewdir = normalize(viewpos - fragpos);
    //vec3 reflectdir = reflect(-lightdir, norm);
    
    //float spec = pow(max(dot(viewdir, reflectdir), 0.0), 32);
    //vec3 specular = spec * color_fragment;
    
    //vec3 result = (color_fragment * specular) * texture2D(texture, texcoords_fragment)
    //gl_FragColor = vec4(result, 1.0);
    
    normal = normalize(normal_fragment);
    gl_FragColor = color_fragment * texture2D(texture, texcoords_fragment);
}
