#version 140
#extension GL_ARB_compatibility: enable

in vec4 p;
in vec3 normal;
in vec4 color;

uniform vec4 specularConst;
uniform vec4 diffuseConst;
uniform vec4 ambientConst;

uniform float alpha;


void main()
{	

	vec3 outColor = vec3(0,0,0);
	
	for (int i = 0 ; i < 4; ++i) {
		  vec3 lightDir =  normalize(vec3(gl_LightSource[i].position - p));
		// diffuse shading
		vec3 new_normal = normalize (normal);
		vec3 viewDir = normalize (vec3(-p));
		float diff = max(dot(new_normal, lightDir), 0.0);
		
		// specular shading
		vec3 reflectDir = reflect(-lightDir, normal);
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), gl_FrontMaterial.shininess);
		// attenuation
		float distance    = length(gl_LightSource[i].position  - p);
		float attenuation = 1.0 / (gl_LightSource[i].constantAttenuation +
				gl_LightSource[i].linearAttenuation * distance +
				gl_LightSource[i].quadraticAttenuation * distance * distance);

		// combine results
		//vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, TexCoords));
		vec3 ambient =  vec3(gl_LightSource[i].ambient * gl_FrontMaterial.diffuse);
		
		//vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, TexCoords));
		vec3 diffuse =  vec3(gl_LightSource[i].diffuse * diff * gl_FrontMaterial.diffuse);
		vec3 specular = vec3(gl_LightSource[i].specular* spec * gl_FrontMaterial.specular);		
		ambient  *= attenuation;
		diffuse  *= attenuation;
		specular *= attenuation;
		//outColor +=		(ambient + diffuse + specular);
		outColor += diff;
	}
	outColor = clamp (outColor , 0 , 1);
	gl_FragColor = vec4(outColor * color , 1.0);
	

	
}




