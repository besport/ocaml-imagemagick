#!/usr/bin/env ocaml
(* #directory "+libMagick" ;; *)
#load "magick.cma" ;;
open Magick ;;
open Imper ;;

#load "unix.cma" ;;


let argc = Array.length Sys.argv in
if (argc < 2) then
  begin prerr_endline ("Usage:\n" ^ Sys.argv.(0) ^ " <image file>") ; exit 1 end
;;

let get_size file =
  let stats = Unix.stat file in
  let float_bytes_size = float_of_int stats.Unix.st_size in
  let size =
    if float_bytes_size > 1024.0
    then ( (Printf.sprintf "%.1f" (float_bytes_size /. 1024.0)) ^ " K")
    else ( (string_of_float float_bytes_size) )
  in
  size
;;

let () =
  let t_img = read_image Sys.argv.(1) in
  let image_type = get_image_type t_img in

  display t_img;

  let width  = get_image_width  t_img
  and height = get_image_height t_img in
  Printf.printf "\t original: width = %d  height = %d\n"
                    width height ;

  let size = get_size Sys.argv.(1) in
  print_endline ("  original file size " ^ size);


  (* Here is the maximum dimention in pixels of the resulting image: *)
  let thumb = 120 in


  let (thumb_width, thumb_height) =
    if (width = height) then
      (thumb, thumb)
    else
    if (width > height) then
      (thumb, (thumb * height / width) )
    else
      ((thumb * width / height) , thumb)
  in
  thumbnail t_img  thumb_width thumb_height;


  let new_width  = get_image_width  t_img
  and new_height = get_image_height t_img in
  Printf.printf "\t thumbnail: width = %d  height = %d\n"
                    new_width new_height;

  set_image_type t_img image_type;
  write_image t_img "/tmp/thumbnail.jpg";

  let size = get_size "/tmp/thumbnail.jpg" in
  print_endline ("  thumbnail size " ^ size);

  display t_img;

  print_newline ();
;;


(*  vim: sw=2 ts=2 sts=2 et fdm=marker
 *)
