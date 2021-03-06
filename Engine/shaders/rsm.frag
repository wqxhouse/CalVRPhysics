// orthoDepthMap.frag

#version 120
#extension GL_ARB_texture_rectangle : enable

varying float v_depth;
varying vec4 v_color;

varying vec3 v_worldPosition;
varying vec3 v_worldNormal;

uniform vec3 u_lightPos;

float encodeFlux(vec3 flux)
{
    flux = clamp(flux, 0.0, 1.0);
    float squeezedFlux = flux.x +
    floor( flux.y * 64.0f ) +
    floor( flux.z * 64.0f ) * 64.0f;
    
    return squeezedFlux;
}

vec3 decodeFlux( float h )
{
    vec3 r;
    
    r.z = fract( h / 64.0f / 64.0f );
    r.y = fract( h / 64.0f );
    r.x = fract( h );
    
    return r;
}

// c_precision of 128 fits within 7 base-10 digits
const float c_precision = 128.0;
const float c_precisionp1 = c_precision + 1.0;

/*
 \param color normalized RGB value
 \returns 3-component encoded float
 */
float color2float(vec3 color) {
    color = clamp(color, 0.0, 1.0);
    return floor(color.r * c_precision + 0.5)
    + floor(color.b * c_precision + 0.5) * c_precisionp1
    + floor(color.g * c_precision + 0.5) * c_precisionp1 * c_precisionp1;
}

/*
 \param value 3-component encoded float
 \returns normalized RGB value
 */
vec3 float2color(float value) {
    vec3 color;
    color.r = mod(value, c_precisionp1) / c_precision;
    color.b = mod(floor(value / c_precisionp1), c_precisionp1) / c_precision;
    color.g = floor(value / (c_precisionp1 * c_precisionp1)) / c_precision;
    return color;
}

void main()
{
    // RSM extension
    vec3 lightDir = normalize(u_lightPos - v_worldPosition);
    vec3 normal = normalize(v_worldNormal);
    vec4 flux = v_color * clamp(dot(normal, lightDir), 0.0, 1.0);
    float encodedFlux = encodeFlux(flux.xyz);
    
    vec3 mainLightDirection = normal;
    gl_FragData[0] = vec4(mainLightDirection, encodedFlux);
    
    // resolve singularity, move worldPos by a small amount of normal dir
    if ( dot( mainLightDirection, lightDir ) < 0.0f )
    {
        normal *= -1.0f;
    }
    
    gl_FragData[1] = vec4(v_worldPosition - normal * 0.1 , 1.0);
}