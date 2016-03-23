var camera;
var scene;
var renderer;
var a;

init();
animate();

var glitch = new THREE.MeshPhongMaterial( { map: THREE.TextureLoader('glitch.PNG') } );
var green = new THREE.MeshPhongMaterial( {color: 0x00ff00} );
var blue = new THREE.MeshPhongMaterial( {color: 0x0000ff} );
var red = new THREE.MeshPhongMaterial( {color: 0xff0000} );
  





  
function init() {

var glitch = new THREE.MeshPhongMaterial( { map: THREE.ImageLoader('glitch.png') } );
var green = new THREE.MeshPhongMaterial( {color: 0x00ff00} );
var blue = new THREE.MeshPhongMaterial( {color: 0x0000ff} );
var red = new THREE.MeshPhongMaterial( {color: 0xff0000} );
  
   	scene = new THREE.Scene();
    camera = new THREE.PerspectiveCamera( 50, window.innerWidth / window.innerHeight, 1, 1000);
  
    var light = new THREE.DirectionalLight( 0x00ffff );
    light.position.set( 1, -1, 1 ).normalize();
    scene.add(light);
  
    var cube = new THREE.CubeGeometry( 10, 10 , 10);
    

  
    a = new THREE.Mesh(cube,  glitch);

    
    
    
    a.position.z = -50;
    scene.add( a ); 
    renderer = new THREE.WebGLRenderer();
    renderer.setSize( window.innerWidth, window.innerHeight );
    document.body.appendChild( renderer.domElement );
  
    window.addEventListener( 'resize', onWindowResize, false );
  
    render();
}

function rand(min, max)
{
	return (Math.floor(Math.random() * (max - min + 1)) + min) * (0.01);
}
  
function animate() {
  
  	
	a.rotation.x += 0.01;
	a.rotation.y += 0.01;
  	

  	
  	
  	
    render();
    requestAnimationFrame( animate );
}
  
function render() {
    renderer.render( scene, camera );
}
  
function onWindowResize() {
    camera.aspect = window.innerWidth / window.innerHeight;
    camera.updateProjectionMatrix();
    renderer.setSize( window.innerWidth, window.innerHeight );
    render();
}

