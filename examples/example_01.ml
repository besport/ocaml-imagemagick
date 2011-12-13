#!/usr/bin/env ocaml
(* #directory "+libMagick" ;; *)
#load "magick.cma" ;;
open Magick ;;
open Imper ;;


let argc = Array.length Sys.argv in
if (argc < 2) then begin
  prerr_endline("Usage:\n" ^ Sys.argv.(0) ^ " <black & white image file>");
  exit 1
end
;;


let () =
  let t_img = read_image Sys.argv.(1) in
  let u_img = clone_image t_img in

  print_endline " Here is the original image";
  display t_img;

  blur  u_img  2.4 ();
  modulate  u_img ~brightness:70 ();
  negate  u_img ();

  print_endline " Intermediate processing";
  display  u_img;

  blur  t_img 0.3 ();  (* smooth the path a little *)
  roll  u_img 2 1;
  composite_image  t_img u_img Lighten ();

  print_endline " Here is the result\n";
  display  t_img;
;;

(*  vim: sw=2 ts=2 sts=2 et fdm=marker
 *)
