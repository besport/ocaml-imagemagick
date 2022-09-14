#load "magick.cma"
open Magick
open Magick.CompositeOp

let () =
  let argc = Array.length Sys.argv in
  if (argc < 2) then begin
    prerr_endline ("Usage:\n" ^ Sys.argv.(0) ^ " <black & white image file>");
    exit 1
  end
;;


let () =
  Magick.initialize ();
  let filename = Sys.argv.(1) in
  let img_g = read_image ~filename in
  let img_o = clone img_g in
  let width, height =
    (image_width  img_g,
     image_height img_g)
  in
  let img_h = get_canvas ~width ~height ~color:"#C13A28" in

  print_endline " Here is the original image";
  display  img_g;

  print_endline " Background color";
  display  img_h;

  let img_g = blur img_g ~sigma:1.2 () in

  negate  img_g 1;
  modulate  img_g "60,100,100";
  negate  img_g 1;
  modulate  img_g "60,100,100";

  let img_g = shade img_g ~gray:1 ~azimuth:50.0  ~elevation:30.0 in

  negate  img_g 1;
  print_endline " Intermediate processing";
  display  img_g;

  composite  img_h img_g ~compose:Modulate ();

  print_endline " Composite";
  display  img_h;

  let img_o = blur img_o ~sigma:0.3 () in
  composite  img_h img_o ~compose:Lighten ();

  print_endline " Here is the result\n";
  display  img_h;
;;

