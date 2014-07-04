<?php // (C) Copyright Bobbing Wide 2013 

/**
 * Implement bw_form_field_ hook for "rating"
 *
 * We use jQuery raty to display the rating field as a set of stars
 * This requires a simple div with the ID set to the selector
 *
 * @link http://wbotelhos.com/raty
 *
 * scoreName: 'score' Name of the hidden field that holds the score value.
 * score: current value of the score
 * path: URL path for the images displayed 
 * readOnly: true when be displayed by bw_theme_field_rating()
 */
function bw_form_field_rating( $name, $type, $title, $value, $args ) {
  $selector = oikr8_enqueue_jquery( $name, $value );
  $lab = label( $name, $title );
  $sediv = retstag( "div", $type, $selector ) ;
  $sediv .= retetag( "div" );   
  bw_tablerow( array( $lab, $sediv ));
}

/**
 * Theme a rating field for display
 *
 * When displayed the field is read only.
 *
 * @param string $key - field name e.g. _dtib_rating
 * @param mixed $value - post metadata value
 * @param array $field - the field structure if defined using bw_register_field()
 */
function bw_theme_field_rating( $key, $value, $field ) {
  $value = bw_array_get( $value, 0, $value );
  //bw_backtrace();
  $selector = oikr8_enqueue_jquery( $key, $value, true );
  span( $key, $selector );
  epan();
  // e( $value );
} 

/**
 * Return a unique selector ID for the star rating field
 */
function oikr8_selector( $prefix="star" ) {
  static $star_id = 0;
  $star_id++;
  return( "$prefix-$star_id" );
} 

/**
 * Enqueue the raty jQuery for the field $name with value $value
 * 
 * @param string $name - the field name (e.g. _dtib_rating )
 * @param string $value - the current value - may be null
 * @return string $selector - the selector for jQuery raty to hook into
 */
function oikr8_enqueue_jquery( $name, $value, $readonly=false ) {
  oik_require( "shortcodes/oik-jquery.php" );
  oik_require( "includes/bw_jquery.inc" );
  add_filter( "bw_jquery_script_url", "oikr8_jquery_script_url", 10, 3 );
  bw_jquery_enqueue_script( "raty", true );
  $selector = oikr8_selector("star-$name");
  $parms = bw_jkv( array( "scoreName" => $name, "score" => $value, "path" => oikr8_icon_path(), "readOnly" => $readonly ));
  bw_jquery( "#$selector", "raty", $parms );
  return( $selector );
}  

/**
 * Return the URL for the image directory used by jQuery raty
 *
 * Note: the lib folder sits in the directory below this file.
 * 
 * @return string - the URL for the image directory
 */
function oikr8_icon_path() {
  $icon_path = plugin_dir_url( __FILE__ ) ;
  $icon_path .= "lib/img";
  //bw_trace2( $icon_path );
  return( $icon_path );
}

/**
 * Implement "bw_jquery_script_url" filter to locate the jquery.raty.js or jquery.raty.min.js file
 * 
 * @param string $script_url - the URL for the jQuery file
 * @param string $script - the script name
 * @param bool $debug - script debug flag
 * @return string - the location of the jQuery raty file
 */
function oikr8_jquery_script_url( $script_url, $script, $debug ) {
  //bw_backtrace();
  if ( $script == "raty" ) {
    $script_url = plugin_dir_url( __FILE__ ) ;
    $script_url .= "lib/";
    if ( $debug ) {
      $script_url .= "jquery.raty.js";
    } else { 
      $script_url .= "jquery.raty.min.js";
    }    
  }
  //bw_trace2( $script_url, "script_url");
  return( $script_url );
}

