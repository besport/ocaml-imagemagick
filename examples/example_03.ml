#!/usr/bin/env ocaml
(* #directory "+libMagick" ;; *)
#load "magick.cma" ;;
open Magick ;;
open Imper ;;


let argc = Array.length Sys.argv in
if (argc < 2) then begin
  prerr_endline ("Usage:\n" ^ Sys.argv.(0) ^ " <black & white image file>");
  exit 1
end
;;


let () =
  let img_g = read_image Sys.argv.(1) in
  let img_o = clone_image img_g in
  let width, height =
    get_image_width  img_g,
    get_image_height img_g
  in
  let img_h = get_canvas ~width ~height ~color:"#C13A28" in

  print_endline " Here is the original image";
  display  img_g;

  print_endline " Background color";
  display  img_h;

  blur  img_g 1.2 ();

  negate  img_g ();
  modulate  img_g ~brightness:60 ();
  negate  img_g ();
  modulate  img_g ~brightness:60 ();

  shade  img_g ~gray:MagickTrue ~azimuth:50.0  ~elevation:30.0 ();
  negate  img_g ();
  print_endline " Intermediate processing";
  display  img_g;

  composite_image  img_h img_g ~compose:Modulate ();

  print_endline " Composite";
  display  img_h;

  blur  img_o 0.3 ();
  composite_image  img_h img_o ~compose:Lighten ();

  print_endline " Here is the result\n";
  display  img_h;
;;


(*  vim: sw=2 ts=2 sts=2 et fdm=marker
 *)
