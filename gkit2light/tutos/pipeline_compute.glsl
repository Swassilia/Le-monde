
 #version 430
  
 #ifdef VERTEX_SHADER
  
 layout(std430, binding= 0) readonly buffer transformedData
 {
     vec4 transformed[];
 };
  
 void main( )
 {
     gl_Position= vec4(transformed[gl_VertexID].x*3,transformed[gl_VertexID].y*3, transformed[gl_VertexID].z*3,transformed[gl_VertexID].z*3 );
 }
 #endif
  
 #ifdef FRAGMENT_SHADER
  
 out vec4 fragment_color;
  
 void main( )
 {
     fragment_color= vec4(1, 1, 0, 1);
 }
 #endif