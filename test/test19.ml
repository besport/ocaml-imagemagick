
let load_file f =
  let ic = open_in f in
  let n = in_channel_length ic in
  let s = Bytes.create n in
  really_input ic s 0 n;
  close_in ic;
  (Bytes.unsafe_to_string s)


let () =
  Magick.initialize ();
  let blob = load_file "image.png" in
  let img = Magick.blob_to_image ~blob in
  Magick.display img;
  Magick.destroy_image img;
  Magick.destroy ();
;;

