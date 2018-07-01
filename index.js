document.addEventListener("DOMContentLoaded", function(){
    document.body.addEventListener("dragenter", cancelEvent);
    document.body.addEventListener("dragover", cancelEvent);
    document.body.addEventListener("drop", dropFile);
});

function cancelEvent( event ){
    event.stopPropagation();
    event.preventDefault();
}

let mbc0;

function dropFile( event ){
    cancelEvent( event );
	
    var dt = event.dataTransfer;
    var files = dt.files;
    var out = [];
    var pendingPal = 1;
    var pending = 0;

    if( !mbc0 ){
	fetch('mbc0.bin')
	    .then( rsp => rsp.arrayBuffer() )
	    .then( ab =>{
		mbc0 = new Uint8Array(ab);
		load();
	    });
    }else{
	load();
    }

    function load(){
	for (var i = 0; i < files.length; i++) {
	    let file = files[i];
	    let fr = new FileReader();
	    fr.onload = evt => process( new Uint8Array(fr.result), file.name.replace(/\.[a-z]+$/i, '') );
	    fr.readAsArrayBuffer( file );	
	}
    }

    function process( ROM, name ){

	if( ROM[0x147] ){
	    log( name + " bad mapper: " + ROM[0x147] );
	    return;
	}

	if( ROM.length >= 0x10000 ){
	    log( name + " too big!" );
	    return;		 
	}
	
	let bin = new Uint8Array( mbc0.length );
	bin.set( mbc0 );
	bin.set( ROM, 0x115cc );
	
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
	out.appendChild(li);
	if( typeof msg == "string" ){
	    li.textContent = msg;
	}else{
	    li.appendChild( msg );
	}
    }

    
}
