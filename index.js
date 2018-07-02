document.addEventListener("DOMContentLoaded", function(){
    document.body.addEventListener("dragenter", cancelEvent);
    document.body.addEventListener("dragover", cancelEvent);
    document.body.addEventListener("drop", dropFile);
});

function cancelEvent( event ){
    event.stopPropagation();
    event.preventDefault();
}

let pal = new Uint32Array(16);
let pal8 = new Uint8Array(pal.buffer);

let mappers = {};

fetch('mbc0.bin')
    .then( rsp => rsp.arrayBuffer() )
    .then( ab =>{
	mappers[0] = {
	    bin:new Uint8Array(ab),
	    binOffset:0,
	    palOffset:0,
	    max: 0x10000
	};
    });

fetch('mbc1.bin')
    .then( rsp => rsp.arrayBuffer() )
    .then( ab =>{
	mappers[1] = {
	    bin:new Uint8Array(ab),
	    binOffset:0,
	    palOffset:0,
	    max: 140*1024
	};
    });

function color( str ){
    let v = parseInt(str, 16);
    let b = (v & 0xFF) / 0xFF * 0x1F; v >>>= 8;
    let g = (v & 0xFF) / 0xFF * 0x3F; v >>>= 8;
    let r = (v & 0xFF) / 0xFF * 0x1F;
    return ((r<<11) | (g<<5) | b) << 3;
}

function dropFile( event ){
    cancelEvent( event );
	
    var dt = event.dataTransfer;
    var files = dt.files;
    var out = [];
    var pendingPal = 1;
    var pending = 0;

    for( let i=0; i<16; ++i ){
	let inp = document.getElementById("c" + i);
	pal[i] = color(inp.value.substr(1));
    }

    for (var i = 0; i < files.length; i++) {
	let file = files[i];
	let fr = new FileReader();
	
	fr.onload = (function(fr, file){
	    
	    if( /.*\.zip$/i.test(file.name) ){
		
		JSZip.loadAsync( fr.result )
		    .then( z => {
			for( let k in z.files )
			    if( /.*\.gb/i.test(k) )
				z.file(k).async("arraybuffer").then( z => {
				    process(
					new Uint8Array(z),
					k.replace(/\.[a-z]+$/i, '')
				    );
				});
		    });
		
	    }else{		
		process( new Uint8Array(fr.result), file.name.replace(/\.[a-z]+$/i, '') );
	    }
	    
	}).bind( null, fr, file );
	
	fr.readAsArrayBuffer( file );	
    }

    function process( ROM, name ){

	let mapper = mappers[ ROM[0x147] ];
	
	if( !mapper ){
	    log( name + " bad mapper: " + ROM[0x147] );
	    return;
	}

	if( ROM.length >= mapper.max ){
	    log( name + " too big!" );
	    return;		 
	}

	if( !mapper.binOffset ){
	    mapper.binOffset = -1;
	    let u32 = new Uint32Array( mapper.bin.buffer );
	    for( let i=0; i<u32.length; ++i ){
		if( u32[i] == 0xEFBEADDE &&  mapper.bin[(i+1)<<2] == 1 ){
		    mapper.binOffset = i<<2;
		    break;
		}
	    }
	}


	if( !mapper.palOffset ){
	    mapper.palOffset = -1;
	    let u32 = new Uint32Array( mapper.bin.buffer );
	    for( let i=0; i<u32.length; ++i ){
		if( u32[i] == 0xEFBEADDE &&  mapper.bin[(i+1)<<2] == 2 ){
		    mapper.palOffset = i<<2;
		    break;
		}
	    }
	}
	
	let bin = new Uint8Array( mapper.bin.length );
	bin.set( mapper.bin );
	bin.set( ROM, mapper.binOffset );
	if( mapper.palOffset != -1 )
	    bin.set( pal8, mapper.palOffset );
	
	let url = URL.createObjectURL( new Blob([bin.buffer], {type:'application/bin'}) );
	let a = document.createElement('A');
	a.href = url;
	a.textContent = name;
	a.setAttribute("download", name + ".bin");
	log( a );
	
    }

    function log( msg ){
	let out = document.getElementById("out");
	let li = document.createElement("li");
	li.onclick = _ => out.removeChild(li);
	out.appendChild(li);
	if( typeof msg == "string" ){
	    li.textContent = msg;
	}else{
	    li.appendChild( msg );
	}
    }

    
}
