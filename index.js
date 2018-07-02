
let pal = new Uint32Array(16);
let pal8 = new Uint8Array(pal.buffer);

let mappers = {};
let palettes = {
    "GBC Up":[
	"#000000", "#833100", "#FFAD63", "#FFFFFF",
	"#000000", "#833100", "#F7C4A5", "#FFFFFF",
	"#000000", "#833100", "#FFAD63", "#FFFFFF",
	"#000000", "#833100", "#FFAD63", "#FFFFFF"
    ],

    "GBC Up+A":[
	"#000000", "#943A3A", "#FF8584", "#FFFFFF",
	"#000000", "#E60000", "#FF8584", "#FFFFFF",
	"#000000", "#008300", "#7BFF30", "#FFFFFF",
	"#000000", "#0000FE", "#65A49B", "#FFFFFF"
    ],

    "GBC Up+B":[
	"#5B3109", "#846B29", "#CE9C85", "#FFE7C5",
	"#000000", "#6B5331", "#A58451", "#FFFFFF",
	"#000000", "#833100", "#FFAD63", "#FFFFFF",
	"#000000", "#833100", "#FFAD63", "#FFFFFF"
    ]

};

let map = [
    3,2,1,0,
    15,14,13,12,
    7,6,5,4,
    11,10,9,8
];

document.addEventListener("DOMContentLoaded", function(){
    document.body.addEventListener("dragenter", cancelEvent);
    document.body.addEventListener("dragover", cancelEvent);
    document.body.addEventListener("drop", dropFile);

    let exp = document.getElementById("export");

    let pc = document.getElementById("palContainer");
    for( let name in palettes ){
	let pe = document.createElement("li");
	pe.textContent = name;
	pc.appendChild( pe );
	pe.onclick = loadPalette.bind( null, palettes[name] );
    }

    [...document.querySelectorAll("input[type=color]")]
	.forEach( el => el.onchange = _ => exp.style.display = "inline" );

    exp.onclick = _ => {
	
	let c = [];
	for( let i=0; i<16; ++i ){
	    c[i] = '"' + document.getElementById("c" + map[i]).value + '"';
	}

	window.open("about:blank", "", "width=350,height=200,_blank").document.write( `
{
	"PALETTE_NAME":[
		${c[0]}, ${c[1]}, ${c[2]}, ${c[3]},
		${c[4]}, ${c[5]}, ${c[6]}, ${c[7]},
		${c[8]}, ${c[9]}, ${c[10]}, ${c[11]},
		${c[12]}, ${c[13]}, ${c[14]}, ${c[15]}
	]
}
`.replace(/\n/g,'<br/>').replace(/\t/g, '&nbsp;&nbsp;') );
	
    };
});

function loadPalette( colors ){
    for( let i=0; i<16; ++i ){
	document.getElementById("c" + map[i]).value = colors[i];
    }
}

function cancelEvent( event ){
    event.stopPropagation();
    event.preventDefault();
}

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
