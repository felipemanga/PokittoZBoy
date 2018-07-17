let borderP = new Uint16Array( 256 );
let borderT = new Uint8Array( 220*16 );
let borderB = new Uint8Array( 220*16 );
let borderL = new Uint8Array( 30*(176-16-16) );
let borderR = new Uint8Array( 30*(176-16-16) );

let borders = 
` black.png
  abugs.png
  advlolo.png
  akazukin.png
  aladdin.png
  alfred.png
  animalbreed-1.png
  animalbreed2-1.png
  animalbreed2-2.png
  animalbreed2-3.png
  animalbreed-2.png
  animalbreed3-1.png
  animalbreed3-2.png
  animalbreed3-3.png
  animalbreed3-4.png
  animalbreed3-5.png
  animaniacs.png
  anotherbible-1.png
  anotherbible-2.png
  aoki.png
  aqua.png
  arcadeclas1-1.png
  arcadeclas1-2.png
  arcadeclas1-3.png
  arcadeclas-1.png
  arcadeclas2-1.png
  arcadeclas2-2.png
  arcadeclas2-3.png
  arcadeclas-2.png
  arcadeclas3-1.png
  arcadeclas3-2.png
  arcadeclas4-1.png
  arcadeclas4-2.png
  arcadeclas4-3.png
  arlebuoken.png
  ateleirmarie.png
  atelierelie.png
  azure.png
  bakenoh-1.png
  bakenoh-2.png
  bakutsu.png
  balloon-1.png
  balloon-2.png
  battlearena.png
  battlecrush.png
  bdaman.png
  beatmania1-1.png
  beatmania1-2.png
  beatmania2-1.png
  beatmania2-2.png
  beauty.png
  bikiruman.png
  blaster.png
  blockuzu.png
  bombermancol-1.png
  bombermancol-2.png
  bombermancol-3.png
  bombermancol-4.png
  bombermancol-5.png
  bombermangb1.png
  bombermangb3-1.png
  bombermangb3-2.png
  bomberusa-1.png
  bomberusa-2.png
  bombquest-1.png
  bombquest-2.png
  bonkrev.png
  brain.png
  bubble.png
  bugscol-1.png
  bugscol-2.png
  bugscol-3.png
  burger.png
  captsu-1.png
  captsu-2.png
  castleleg.png
  chasehq.png
  chibi.png
  choroq-1.png
  choroq-2.png
  columns.png
  conker.png
  crayon4-1.png
  crayon4-2.png
  crayon4-3.png
  crayon5.png
  daffy-1.png
  daffy-2.png
  daikai2.png
  daikai.png
  daiku.png
  dbzgeki.png
  dbzgoku.png
  dear.png
  decconanchika.png
  decconangiwa.png
  decconankara.png
  decconankiga.png
  decconannoro.png
  desert.png
  dino3.png
  dino4.png
  dino.png
  donkeyland2.png
  donkeyland3.png
  donkeyland.png
  donkey.png
  doraemondx.png
  dorakart2.png
  dorakart.png
  dragondance.png
  drawar12-1.png
  drawar12-2.png
  drawar12-3.png
  drawar12-4.png
  drawar12-5.png
  drawar12-6.png
  drawar12-7.png
  drawarmon1-1.png
  drawarmon1-2.png
  drawarmon1-3.png
  drawarmon1-4.png
  drawarmon2-1.png
  drawarmon2-2.png
  dunsavior.png
  dxmonopoly.png
  exchange.png
  fairy.png
  fifa2000.png
  fifa96.png
  fifa97.png
  fifa98.png
  fifa.png
  frommabo.png
  fromslam1.png
  fromslam2-1.png
  fromslam2-2.png
  fromyume.png
  furai.png
  gamecamera.png
  gamegallery-1.png
  gamegallery-2.png
  gamegallery-3.png
  gamegallery-4.png
  gamegallery-5.png
  gamegallery-6.png
  gamelife-1.png
  gamelife-2.png
  gamera-1.png
  gamera-2.png
  gamera-3.png
  gamera-4.png
  gametama2-1.png
  gametama2-2.png
  gametama3-1.png
  gametama3-2.png
  gamewars2.png
  gamewarsturbo.png
  gamewatch1-1.png
  gamewatch1-2.png
  gamewatch1-3.png
  gamewatch1-4.png
  gamewatch1-5.png
  gamewatch1-6.png
  gamewatch1-7.png
  gamewatch1-8.png
  gamewatch2-10.png
  gamewatch2-11.png
  gamewatch2-1.png
  gamewatch2-2.png
  gamewatch2-3.png
  gamewatch2-4.png
  gamewatch2-5.png
  gamewatch2-6.png
  gamewatch2-7.png
  gamewatch2-8.png
  gamewatch2-9.png
  gamewatch3-10.png
  gamewatch3-11.png
  gamewatch3-12.png
  gamewatch3-13.png
  gamewatch3-14.png
  gamewatch3-15.png
  gamewatch3-16.png
  gamewatch3-17.png
  gamewatch3-18.png
  gamewatch3-19.png
  gamewatch3-1.png
  gamewatch3-2.png
  gamewatch3-3.png
  gamewatch3-4.png
  gamewatch3-5.png
  gamewatch3-6.png
  gamewatch3-7.png
  gamewatch3-8.png
  gamewatch3-9.png
  gbgenjincol-1.png
  gbgenjincol-2.png
  genjin.png
  goack.png
  godmedi.png
  goemonkuro.png
  goemonmono.png
  gohit-1.png
  gohit-2.png
  gohit-3.png
  golfdai.png
  golfou.png
  greatbattle-1.png
  greatbattle-2.png
  gurander-1.png
  gurander-2.png
  gurander-3.png
  guruguru.png
  hamster.png
  hanasaka.png
  harvest.png
  hayaosi.png
  hellobeads.png
  hellomagic.png
  hellosweet.png
  hercules.png
  hexite.png
  holy.png
  honkaku.png
  honuchi.png
  hoshi2.png
  hugo.png
  hunch.png
  initial.png
  intrally.png
  intsoccer99.png
  intsoccer.png
  inttrack.png
  ironman.png
  itsudemo.png
  jack.png
  james.png
  jbig.png
  jinsei.png
  jissen.png
  jleague95.png
  jleague.png
  joryuu.png
  jungle.png
  jurassic.png
  juukou.png
  kakutougekitou.png
  kakutoukettou.png
  kandume.png
  kanji2.png
  kanji.png
  kanjiro.png
  karaosa.png
  karaziken.png
  kaseki2.png
  kaseki.png
  katou.png
  kawai.png
  keipow.png
  keispe.png
  ken.png
  kettou.png
  killer.png
  kindaichi.png
  kiniku2.png
  kiniku.png
  kirby2.png
  kirbyblock.png
  kirbyno.png
  kirbystar.png
  kitarou.png
  kof95.png
  kofheat-1.png
  kofheat-2.png
  koguru.png
  kokiatsu.png
  konamigb1-1.png
  konamigb1-2.png
  konamigb1-3.png
  konamigb1-4.png
  konamigb2-1.png
  konamigb2-2.png
  konamigb2-3.png
  konamigb2-4.png
  konamigb3-1.png
  konamigb3-2.png
  konamigb3-3.png
  konamigb3-4.png
  konamigb4-1.png
  konamigb4-2.png
  konamigb4-3.png
  konamigb4-4.png
  konchu2.png
  konchu.png
  koushien.png
  kumano.png
  kusou.png
  legriver-1.png
  legriver-2.png
  legriver-3.png
  legriver-4.png
  legzelda.png
  lil.png
  little.png
  lodoss-1.png
  lodoss-2.png
  loppi.png
  luca.png
  mach.png
  maden2000.png
  maden96.png
  maden97.png
  mahjou.png
  mahou1-1.png
  mahou1-2.png
  mahou1-3.png
  mahou1-4.png
  mahou1-5.png
  mahou2.png
  mahoujin.png
  mahquest.png
  majoko.png
  mariono-1.png
  mariono-2.png
  mariono-3.png
  mariono-4.png
  mariono-5.png
  mariono-6.png
  mariono-7.png
  mariopicross-1.png
  mariopicross-2.png
  mariopicross-3.png
  mariopicross-4.png
  mariopicross-5.png
  mariopicross-6.png
  mariopicross-7.png
  marmalade.png
  masakari-1.png
  masakari-2.png
  masakari-3.png
  mathias.png
  mazeko1.png
  mazeko2-1.png
  mazeko2-2.png
  meda2kabu.png
  meda2kuwa.png
  meda2part.png
  medacardkabu.png
  medacardkuwa.png
  medakabu.png
  medakawa.png
  medaparts2.png
  medaparts.png
  megaman5.png
  megami2.png
  men.png
  mickeymagic.png
  mickeytokio.png
  midorin-1.png
  midorin-2.png
  mini42-1.png
  mini42-2.png
  mini4.png
  minimax.png
  mini.png
  mmprmovie.png
  mmpr.png
  mogu.png
  moguq-1.png
  moguq-2.png
  moguq-3.png
  moguq-4.png
  moguq-5.png
  moguq-6.png
  moguq-7.png
  moguq-8.png
  moguq-9.png
  mogura.png
  mole.png
  momo1-1.png
  momo1-2.png
  momo2.png
  momoden2.png
  momojr.png
  moneyidol.png
  monkey.png
  monopoly.png
  monsterrace2.png
  monsterraceother.png
  monsterrace.png
  monsterranch.png
  mortal4.png
  mulan.png
  mystical.png
  namco1-1.png
  namco1-2.png
  namco1-3.png
  namco1-4.png
  namco1-5.png
  namco2-1.png
  namco2-2.png
  namco2-3.png
  namco2-4.png
  namco2-5.png
  namco3-1.png
  namco3-2.png
  namco3-3.png
  namco3-4.png
  namco3-5.png
  nba3on3.png
  nbalive.png
  nbazone-1.png
  nbazone-2.png
  nectaris.png
  netgarou2.png
  netkof95.png
  netkof96-1.png
  netkof96-2.png
  netreal.png
  netsamurai-1.png
  netsamurai-2.png
  netsamurai-3.png
  netsamurai-4.png
  nettosh.png
  networld.png
  newsd.png
  nhl2000.png
  nhl95.png
  nhl96.png
  nihon.png
  ninku2-1.png
  ninku2-2.png
  ninku2-3.png
  ninku.png
  nintama.png
  nintamapuz.png
  nobunaga2.png
  obelix.png
  ohasta.png
  olympic.png
  oni5.png
  othelo-1.png
  othelo-2.png
  otogi.png
  ou.png
  owarai.png
  pachinkocr.png
  pachinkodata.png
  pachinkogai.png
  pachi.png
  pac.png
  page.png
  pga96.png
  pga.png
  phantom-1.png
  phantom-2.png
  phantom-3.png
  picross2-1.png
  picross2-2.png
  picross2-3.png
  picross2-4.png
  picross2-5.png
  picross2-6.png
  picross2-7.png
  poca.png
  pocbomb-1.png
  pocbomb-2.png
  pocbombj-1.png
  pocbombj-2.png
  poccamera.png
  poccolor.png
  poccol.png
  pocden1-1.png
  pocden1-2.png
  pocden1-3.png
  pocden1-4.png
  pocden1-5.png
  pocden1-6.png
  pocden2-1.png
  pocden2-2.png
  pocfam.png
  pocghougi.png
  pocgi.png
  pocjock.png
  pockan.png
  pockyo.png
  poclov2.png
  poclov.png
  pocpuyo2.png
  pocpuyosun.png
  pokeama.png
  pokeargento.png
  pokeargent.png
  pokeazul.png
  pokeblaue.png
  pokebleue.png
  pokeblue.png
  pokeblu.png
  pokegelb.png
  pokegialla.png
  pokegoldene.png
  pokegold.png
  pokejaune.png
  pokeoro.png
  pokeor.png
  pokepineuro.png
  pokepin.png
  pokeplata.png
  pokered.png
  pokeroja.png
  pokerossa.png
  pokerote.png
  pokerouge.png
  pokesilber.png
  pokesilver.png
  poketrading-1.png
  poketrading-2.png
  poketrading-3.png
  poketrading-4.png
  pokevoro.png
  pokeyellow.png
  pomonblue.png
  pomongoldbeta.png
  pomongold.png
  pomongreen.png
  pomonpika.png
  pomonpin.png
  pomonred.png
  pomonsilbeta.png
  pomonsil.png
  pomontrade-1.png
  pomontrade-2.png
  pomontrade-3.png
  pomontrade-4.png
  ponko-1.png
  ponko-2.png
  ponko-3.png
  ponko-4.png
  ponko-5.png
  powerpro.png
  powpro1.png
  powpro2.png
  powquest.png
  poyon.png
  prokiwa2.png
  prokiwa.png
  protsu.png
  puchi.png
  puri1.png
  puri2.png
  puri3.png
  puyogai.png
  puzzle-1.png
  puzzle-2.png
  questcam.png
  quest.png
  realpro.png
  retrieve.png
  rev.png
  road.png
  robosun.png
  robponbom.png
  robponmoon.png
  robponstar.png
  robponsun.png
  rockn-10.png
  rockn-11.png
  rockn-1.png
  rockn-2.png
  rockn-3.png
  rockn-4.png
  rockn-5.png
  rockn-6.png
  rockn-7.png
  rockn-8.png
  rockn-9.png
  rugmovie.png
  saihai.png
  sakata.png
  same-1.png
  same-2.png
  san.png
  sanrio.png
  sdex.png
  sdgai1.png
  sdgai2.png
  selection-1.png
  selection-2.png
  senkai.png
  sf2-1.png
  sf2-2.png
  sf2-3.png
  sf2-4.png
  sf2-5.png
  sf2-6.png
  sf2-7.png
  sf2-8.png
  sf2-9.png
  shangj.png
  shang.png
  shaq.png
  shinaka.png
  shinkuro.png
  shougi.png
  shuto.png
  small.png
  smurfs-1.png
  smurfs-2.png
  smurfs-3.png
  snoopy.png
  space-1.png
  space-2.png
  spirou.png
  sports.png
  ssspiner.png
  starocean.png
  starsweep-1.png
  starsweep-2.png
  starsweep-3.png
  starsweep-4.png
  starwars.png
  supblack-1.png
  supblack2-1.png
  supblack2-2.png
  supblack2-3.png
  supblack2-4.png
  supblack2-5.png
  supblack2-6.png
  supblack2-7.png
  supblack2-8.png
  supblack-2.png
  supblack-3.png
  supblack-4.png
  supblack-5.png
  supblack-6.png
  supblack-7.png
  supblack-8.png
  supbombdx-1.png
  supbombdx-2.png
  supbombdx-3.png
  supbombdx-4.png
  supchin123-1.png
  supchin123-2.png
  supchin123-3.png
  supchin123-4.png
  supchin3d.png
  supchin3.png
  supchinfig.png
  superb-1.png
  superb-2.png
  supergameboy-10.png
  supergameboy-11.png
  supergameboy-12.png
  supergameboy-13.png
  supergameboy-14.png
  supergameboy-15.png
  supergameboy-16.png
  supergameboy-17.png
  supergameboy-18.png
  supergameboy-19.png
  supergameboy-1.png
  supergameboy-20.png
  supergameboy2-10.png
  supergameboy2-11.png
  supergameboy2-12.png
  supergameboy2-13.png
  supergameboy2-14.png
  supergameboy2-15.png
  supergameboy2-16.png
  supergameboy2-17.png
  supergameboy2-18.png
  supergameboy2-19.png
  supergameboy-21.png
  supergameboy2-1.png
  supergameboy2-20.png
  supergameboy2-21.png
  supergameboy2-22.png
  supergameboy2-23.png
  supergameboy2-24.png
  supergameboy2-25.png
  supergameboy-22.png
  supergameboy2-2.png
  supergameboy-23.png
  supergameboy2-3.png
  supergameboy-24.png
  supergameboy2-4.png
  supergameboy-25.png
  supergameboy2-5.png
  supergameboy-26.png
  supergameboy2-6.png
  supergameboy-27.png
  supergameboy2-7.png
  supergameboy-28.png
  supergameboy2-8.png
  supergameboy2-9.png
  supergameboy-2.png
  supergameboy-3.png
  supergameboy-4.png
  supergameboy-5.png
  supergameboy-6.png
  supergameboy-7.png
  supergameboy-8.png
  supergameboy-9.png
  superman.png
  suppachi.png
  suprobot.png
  suptai.png
  survival1.png
  survival2.png
  sweet.png
  sylfam.png
  sylmel.png
  taitovar.png
  tales.png
  tamago-1.png
  tamago-2.png
  tamago-3.png
  tamago-4.png
  tamago-5.png
  tanimura.png
  tetdx-1.png
  tetdx-2.png
  tetplus.png
  tetris2-1.png
  tetris2-2.png
  tetris2-3.png
  tetris2-4.png
  tetris2-5.png
  tetris2-6.png
  tetrisattack-1.png
  tetrisattack-2.png
  tetrisattack-3.png
  tetrisattack-4.png
  tetrisattack-5.png
  tetrisattack-6.png
  tetrisattack-7.png
  tetrisblast-1.png
  tetrisblast-2.png
  tetrisblast-3.png
  tetrisblast-4.png
  tintin.png
  tnn-10.png
  tnn-1.png
  tnn-2.png
  tnn-3.png
  tnn-4.png
  tnn-5.png
  tnn-6.png
  tnn-7.png
  tnn-8.png
  tnn-9.png
  tokimeki-1.png
  tokimeki-2.png
  tokoro.png
  tokyo.png
  totemo-1.png
  totemo-2.png
  totsugeki.png
  toystory1.png
  toystory2.png
  trade.png
  tsumego.png
  tsumeshougi.png
  tsuri1.png
  tsuri2.png
  tv.png
  ultraball.png
  ultrageki-1.png
  ultrageki-2.png
  umi2-1.png
  umi2-2.png
  umi2-3.png
  umi2-4.png
  urban.png
  vegas-1.png
  vegas-2.png
  vegas-3.png
  vegas-4.png
  vegas-5.png
  warioblast.png
  warioland2-1.png
  warioland2-2.png
  warioland2-3.png
  warioland2-4.png
  warioland2-5.png
  warioland2-6.png
  warioland2-7.png
  warioland2-8.png
  warioland2-9.png
  wedding-1.png
  wedding-2.png
  wedding-3.png
  wedding-4.png
  wetrix.png
  wildsnake-1.png
  wildsnake-2.png
  wildsnake-3.png
  wildsnake-4.png
  world98.png
  worldheroes.png
  worldsoc2.png
  worldsoc.png
  yugiduel1.png
  yugiduel2.png
  yugimons-1.png
  yugimons-2.png
  yugimons-3.png
  yuyu.png`.split('\n').map( x => x.trim() );

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
    ],

    "@Jonne - Prince Of Persia":[
	"#000000", "#aa8484", "#535764", "#fff897",
	"#000000", "#e60000", "#ff8584", "#ffff00",
	"#000000", "#008300", "#df826d", "#ffffff",
	"#000000", "#312945", "#5e8db0", "#ffffff"
    ],

    "@Jonne - Sensible Soccer":[
	"#ffffff", "#ffa935", "#239801", "#496239",
	"#000000", "#e60000", "#ff8584", "#ffffff",
	"#ffff00", "#803217", "#7bff30", "#ffffff",
	"#000000", "#f06e0a", "#ffffff", "#ffffff"
    ],

    "@FManga - Asteroids":[
	"#ecebeb", "#9da0a9", "#525363", "#14161c",
	"#83fffd", "#66c3bc", "#2e5c59", "#0f1d1d",
	"#78ffb4", "#50b080", "#2b513d", "#ffffff",
	"#ff6f6f", "#b7595c", "#311818", "#ffffff"
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
    let bs = document.getElementById("border");
    let pc = document.getElementById("palContainer");
    for( let name in palettes ){
	let pe = document.createElement("li");
	pe.textContent = name;
	pc.appendChild( pe );
	pe.onclick = loadPalette.bind( null, palettes[name] );
    }

    [...document.querySelectorAll("input[type=color]")]
	.forEach( el => el.onchange = _ => exp.style.display = "inline" );

    borders.forEach( (b,i) => {
	let o = document.createElement("option");
	o.value = b;
	o.textContent = b.replace(/\.[a-z]+$/i, '');
	bs.appendChild(o);
    });

    bs.onchange = changeBorder;

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

let hasBorder = false;

function changeBorder( evt ){
    let fileName = evt.target.value;
    let box = document.getElementById("box");

    hasBorder = false;

    if( !fileName ){
	borderP.fill(0x0000);
	borderT.fill(0);
	borderB.fill(0);
	borderL.fill(0);
	borderR.fill(0);
	box.classList.remove("border");
	box.style.backgroundImage = '';
	return;
    }
    box.classList.add("border");
    let url = `sgb_borders/${fileName}`;
    box.style.backgroundImage = `url(${url})`;
    
    let img = new Image();
    img.src = url;
    img.onload = loadBorders.bind(null, img);

}

let canvas = document.createElement("canvas");
canvas.width = 220;
canvas.height = 176;
let ctx = canvas.getContext("2d");

function loadBorders( img ){
    hasBorder = true;

    ctx.drawImage( img, canvas.width/2 - img.width/2, canvas.height/2 - img.height/2 );
    let id = ctx.getImageData(0,0,220,176);
    let data = id.data;
    let colorCount = 0;
    let colorIndex = {};

    fillBuffer( borderT, 0, 0, 220, 16 );
    fillBuffer( borderB, 0, 176-16, 220, 16 );
    fillBuffer( borderL, 0, 16, 30, 176-16-16 );
    fillBuffer( borderR, 160+30, 16, 30, 176-16-16 );
    
    function fillBuffer( b, rx, ry, w, h ){
	let i=0;
	for( let y=0; y<h; y++ ){
	    for( let x=0; x<w; x++ ){
		let j = ((y+ry) * 220 + (x+rx)) << 2;
		
		let c = (data[j]/0xFF*0x1F<<11) |
		    (data[j+1]/0xFF*0x3F<<5) |
		    (data[j+2]/0xFF*0x1F);

		let index = colorIndex[c];
		if( index == undefined ){
		    if( colorCount < 256 ){
			colorIndex[c] = colorCount;
			borderP[colorCount] = c;
			index = colorCount++;			
		    }else{
			index = 0;
		    }
		}

		b[i++] = index;
	    }
	}
    }
}

function loadPalette( colors ){
    for( let i=0; i<16; ++i ){
	document.getElementById("c" + map[i]).value = colors[i];
    }
}

function cancelEvent( event ){
    event.stopPropagation();
    event.preventDefault();
}

fetch('mbc0.bin?'+Math.random())
    .then( rsp => rsp.arrayBuffer() )
    .then( ab =>{
	mappers.b0 = {
	    bin:new Uint8Array(ab),
	    binOffset:0,
	    palOffset:0,
	    max: 0x10000
	};
    });

fetch('mbc1.bin?'+Math.random())
    .then( rsp => rsp.arrayBuffer() )
    .then( ab =>{
	mappers.b1 = {
	    bin:new Uint8Array(ab),
	    binOffset:0,
	    palOffset:0,
	    max: 128*1024
	};
    });


fetch('mbc0s.bin?'+Math.random())
    .then( rsp => rsp.arrayBuffer() )
    .then( ab =>{
	mappers.s0 = {
	    bin:new Uint8Array(ab),
	    binOffset:0,
	    palOffset:0,
	    max: 0x10000
	};
    });

fetch('mbc1s.bin?'+Math.random())
    .then( rsp => rsp.arrayBuffer() )
    .then( ab =>{
	mappers.s1 = {
	    bin:new Uint8Array(ab),
	    binOffset:0,
	    palOffset:0,
	    max: 128*1024
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

	    if( /.*\.png$/i.test(file.name) ){

		parseBorder( fr.result );
		
	    }else if( /.*\.json$/i.test(file.name) ){

		parseJSONPalette( fr.result );
		
	    }else if( /.*\.zip$/i.test(file.name) ){
		
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

    function parseBorder( borderab ){
	let buf = new Uint8Array( borderab );
	let url = URL.createObjectURL( new Blob([borderab], {type:'image/png'}) );
	let box = document.getElementById("box");
	box.classList.add("border");
	box.style.backgroundImage = `url(${url})`;
	
	let img = new Image();
	img.src = url;
	img.onload = loadBorders.bind(null, img);	
    }

    function parseJSONPalette( palab ){
	let pal = '';
	let palu8 = new Uint8Array( palab );
	for( let i=0; i<palu8.length; ++i )
	    pal += String.fromCharCode( palu8[i] );
	pal = JSON.parse(pal);
	loadPalette( pal[ Object.keys(pal)[0] ] );
    }

    function parsePal( palab ){
	let pal = '';
	let palu8 = new Uint8Array( palab );
	for( let i=0; i<palu8.length; ++i )
	    pal += String.fromCharCode( palu8[i] );
	pal = pal.split("\n");
	pal.shift();
	pal.shift();
	
    }

    function process( ROM, name ){

	let mapper = mappers[ (hasBorder?'b':'s') + ROM[0x147] ];
	
	if( !mapper ){
	    log( name + " bad mapper: " + ROM[0x147] );
	    return;
	}

	if( ROM.length > mapper.max ){
	    log( name + " too big!" );
	    return;		 
	}

	if( !mapper.binOffset ){
	    let u32 = new Uint32Array( mapper.bin.buffer );
	    let found = 0;
	    let keys = [
		"binOffset",
		"palOffset",
		"btOffset",
		"bbOffset",
		"blOffset",
		"brOffset",
		"bpOffset"
	    ];
	    for( let i=0; i<u32.length; ++i ){
		if( u32[i] == 0xEFBEADDE ){		    
		    mapper[keys[mapper.bin[(i+1)<<2]-1]] = i<<2;
		    found++;
		    if( found == keys.length )
			break;
		}
	    }
	}

	
	let bin = new Uint8Array( mapper.bin.length );
	bin.set( mapper.bin );
	bin.set( ROM, mapper.binOffset );
	bin.set( pal8, mapper.palOffset );
	if( mapper.bpOffset ){
	    bin.set( new Uint8Array(borderP.buffer), mapper.bpOffset );
	    bin.set( borderT, mapper.btOffset );
	    bin.set( borderB, mapper.bbOffset );
	    bin.set( borderL, mapper.blOffset );
	    bin.set( borderR, mapper.brOffset );
	}
	
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
