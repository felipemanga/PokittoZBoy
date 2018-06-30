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
		mbc0 = ab;
		load();
	    });
    }else{
	load();
    }

    function load(){
	for (var i = 0; i < files.length; i++) {
	    let file = files[i];
	    let fr = new FileReader();
	    fr.onload = evt => process( new Uint8Array(fr.result), file.name );
	    fr.readAsArrayBuffer( file );	
	}
    }

    function process( ROM, name ){
	let out = document.getElementById("out");
	let li = document.createElement("li");
	out.appendChild(li);
	let a = document.createElement("a");
	li.appendChild(a);
	a.textContent = name.replace(/\.[a-z]$/i, '') + ROM[0x147];
	
    }

    
}
