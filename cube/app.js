var camera;
var scene;
var renderer;
var a;
var i = 0;
init();
animate();


function init() {
  
    scene = new THREE.Scene();
    camera = new THREE.PerspectiveCamera( 100, window.innerWidth / window.innerHeight, 1, 1000);
  
    var light = new THREE.DirectionalLight( 0xffffff );
    light.position.set( 1, 1, 1 ).normalize();
    
    scene.add(light);
  
    var geometry = new THREE.CubeGeometry( 10, 10, 10);
    var sphere = new THREE.SphereGeometry( 5, 32, 32 );
    
var green = new THREE.MeshPhongMaterial( {color: 0x00ff00} );
var blue = new THREE.MeshPhongMaterial( {color: 0x0000ff} );
var red = new THREE.MeshPhongMaterial( {color: 0xff0000} );
  
    a = new THREE.Mesh(sphere, green );
    
    a1 = new THREE.Mesh(geometry, blue );
    a2 = new THREE.Mesh(geometry, red );
    b = new THREE.Mesh(geometry, green );
    b1 = new THREE.Mesh(geometry, blue );
    b2 = new THREE.Mesh(geometry, red );
    c = new THREE.Mesh(geometry, green );
    c1 = new THREE.Mesh(geometry, blue );
    c2 = new THREE.Mesh(geometry, red );
    

	
	
    
    
    
    a.position.z = -50;
    scene.add( a );
   	a1.position.z = -50;
    a1.position.x =  10;
    scene.add( a1 );
    a2.position.z = -50;
    a2.position.x =  -10;
    scene.add( a2 );
    
    b.position.z = -50;
    b.position.y = 10;
    scene.add( b );
   	b1.position.z = -50;
    b1.position.x =  10;
    b1.position.y = 10;
    scene.add( b1 );
    b2.position.z = -50;
    b2.position.x =  -10;
    b2.position.y = 10;
    scene.add( b2 );
    
    c.position.z = -50;
    c.position.y = -10;
    scene.add( c );
   	c1.position.z = -50;
    c1.position.x =  10;
    c1.position.y = -10;
    scene.add( c1 );
    c2.position.z = -50;
    c2.position.x =  -10;
    c2.position.y = -10;
    scene.add( c2 );
    
    
    
    
  
    renderer = new THREE.WebGLRenderer();
    renderer.setSize( window.innerWidth, window.innerHeight );
    document.body.appendChild( renderer.domElement );
  
    window.addEventListener( 'resize', onWindowResize, false );
  
    render();
}

function rand(min, max)
{
	return (Math.floor(Math.random() * (max - min + 1)) + min) * (0.1);
}
  
function animate() {
    /*a.rotation.x += .04;
    a.rotation.y += .02;
    a.position.y += -.02;
    a1.rotation.x += .05;
    a1.rotation.y += .03;
    a1.position.z += -0.01;
    a2.rotation.x += .06;
    a2.rotation.y += .01;
    a2.position.z += 0.01;*/
  
  
  	a.rotation.x += (rand(-10,10)/10);
  	a1.rotation.x +=(rand(-10,10)/10);
  	a2.rotation.x += (rand(-10,10)/10);
  	a.rotation.y += (rand(-10,10)/10);
  	a1.rotation.y +=(rand(-10,10)/10);
  	a2.rotation.y += (rand(-10,10)/10);
  	a.rotation.z += (rand(-10,10)/10);
  	a1.rotation.z +=(rand(-10,10)/10);
  	a2.rotation.z += (rand(-10,10)/10);
  	
  	a.position.x += (rand(-10,10)/10);
  	a.position.y += (rand(-10,10)/10);
  	a.position.z += (rand(-10,10)/10);
  	a1.position.x += (rand(-10,10)/10);
  	a1.position.y += (rand(-10,10)/10);
  	a1.position.z += (rand(-10,10)/10);
  	a2.position.x += (rand(-10,10)/10);
  	a2.position.y += (rand(-10,10)/10);
  	a2.position.z += (rand(-10,10)/10);
  	
  	b.rotation.x += (rand(-10,10)/10);
  	b1.rotation.x +=(rand(-10,10)/10);
  	b2.rotation.x += (rand(-10,10)/10);
  	b.rotation.y += (rand(-10,10)/10);
  	b1.rotation.y +=(rand(-10,10)/10);
  	b2.rotation.y += (rand(-10,10)/10);
  	b.rotation.z += (rand(-10,10)/10);
  	b1.rotation.z +=(rand(-10,10)/10);
  	b2.rotation.z += (rand(-10,10)/10);
  	
  	b.position.x += (rand(-10,10)/10);
  	b.position.y += (rand(-10,10)/10);
  	b.position.z += (rand(-10,10)/10);
  	b1.position.x += (rand(-10,10)/10);
  	b1.position.y += (rand(-10,10)/10);
  	b1.position.z += (rand(-10,10)/10);
  	b2.position.x += (rand(-10,10)/10);
  	b2.position.y += (rand(-10,10)/10);
  	b2.position.z += (rand(-10,10)/10);
  	
  	c.rotation.x += (rand(-10,10)/10);
  	c1.rotation.x +=(rand(-10,10)/10);
  	c2.rotation.x += (rand(-10,10)/10);
  	c.rotation.y += (rand(-10,10)/10);
  	c1.rotation.y +=(rand(-10,10)/10);
  	c2.rotation.y += (rand(-10,10)/10);
  	c.rotation.z += (rand(-10,10)/10);
  	c1.rotation.z +=(rand(-10,10)/10);
  	c2.rotation.z += (rand(-10,10)/10);
  	
  	c.position.x += (rand(-10,10)/10);
  	c.position.y += (rand(-10,10)/10);
  	c.position.z += (rand(-10,10)/10);
  	c1.position.x += (rand(-10,10)/10);
  	c1.position.y += (rand(-10,10)/10);
  	c1.position.z += (rand(-10,10)/10);
  	c2.position.x += (rand(-10,10)/10);
  	c2.position.y += (rand(-10,10)/10);
  	c2.position.z += (rand(-10,10)/10);
  	
  	
  	// starting from top left. 
  	
  	b2.position.x += -0.01;
  	b2.position.y += 0.01;

  	
  	b.position.y += 0.01;
  	  	  	
  	a2.position.x += -0.01;
  	
  	a1.position.x += 0.01; 
  	
  	b1.position.y += 0.01;
  	b1.position.x += 0.01;  	
  	
  	c1.position.y += -0.01;
  	c1.position.x += 0.01;
  	
  	c.position.y += -0.01;
  	
  	c2.position.y += -0.01;
  	c2.position.x += -0.01;
  	
  	
  	
	
  	camera.rotation.z += 0.01 * Math.tan(i) * Math.cos(i);
  	camera.rotation.z += 0.01;
  	camera.position.z += rand(-10,10);
  	camera.rotation.x += 0.001 * Math.cos(i);
  	camera.rotation.y +=  0.001 * Math.tan(i);
  	camera.position.z = 2 * Math.sin(i);
  
  	
    render();
    requestAnimationFrame( animate );
    i += 0.1;
    
    if (c.position.x < -1.5){location.reload();}
    
}
  
function render() {
    renderer.render( scene, camera );
    camera.lookAt( a );

}
  
function onWindowResize() {
    camera.aspect = window.innerWidth / window.innerHeight;
    camera.updateProjectionMatrix();
    renderer.setSize( window.innerWidth, window.innerHeight );
    render();
}