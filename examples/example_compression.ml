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

(*
let tmp_path = "." ;;
let tmp_path = "/mnt/ramdisk" ;;
*)
let tmp_path = "/tmp" ;;


let compress_to quality image_handle =
  let img_file = (Printf.sprintf "%s/compress-%03d.jpg" tmp_path quality)
  and _img_handle = clone_image image_handle
  in
  set_compression_quality  _img_handle  quality;
  write_image _img_handle img_file;

  let file_size = get_size img_file in
  print_endline(Printf.sprintf "\t jpeg compression %d\tsize %s" quality file_size);

  let result = read_image img_file in
  Sys.remove img_file;
  display result;
;;


let () =
  let t_img = read_image Sys.argv.(1) in

  let file_size = get_size Sys.argv.(1) in
  print_endline(Printf.sprintf "\t original file size %s\n" file_size);

  compress_to    8  t_img;
  compress_to   16  t_img;
  compress_to   30  t_img;
  compress_to   50  t_img;
  compress_to   70  t_img;
  compress_to   80  t_img;
  compress_to   90  t_img;
  compress_to   97  t_img;
  compress_to  100  t_img;

  print_newline ();
;;


(*  vim: sw=2 ts=2 sts=2 et fdm=marker
 *)
