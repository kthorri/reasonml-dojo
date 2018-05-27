module ComposableMap = {
  [@bs.module "react-simple-maps"]
  external composableMap : ReasonReact.reactClass = "ComposableMap";
  [@bs.deriving abstract]
  type projectionconfig = {
    scale: int,
    rotation: array(int),
  };
  [@bs.deriving abstract]
  type jsProps = {
    width: int,
    height: int,
    projection: string,
    projectionConfig: projectionconfig,
  };
  let make = (~width, ~height, ~projection, ~projectionConfig, children) =>
    ReasonReact.wrapJsForReason(
      ~reactClass=composableMap,
      ~props=jsProps(~width, ~height, ~projection, ~projectionConfig),
      children,
    );
};

module ZoomableGroup = {
  [@bs.module "react-simple-maps"]
  external zoomableGroup : ReasonReact.reactClass = "ZoomableGroup";
  [@bs.deriving abstract]
  type jsProps = {
    center: array(int),
    disablePanning: bool,
  };
  let make = (~center, ~disablePanning, children) =>
    ReasonReact.wrapJsForReason(
      ~reactClass=zoomableGroup,
      ~props=jsProps(~center, ~disablePanning),
      children,
    );
};

module Geographies = {
  [@bs.module "react-simple-maps"]
  external geographies : ReasonReact.reactClass = "Geographies";
  [@bs.deriving abstract]
  type jsProps = {
    disableOptimization: bool,
    geography: string,
  };
  let make = (~disableOptimization, ~geography, children) =>
    ReasonReact.wrapJsForReason(
      ~reactClass=geographies,
      ~props=jsProps(~disableOptimization, ~geography),
      children,
    );
};

module Geography = {
  [@bs.module "react-simple-maps"]
  external geographyComponent : ReasonReact.reactClass = "Geography";
  [@bs.deriving abstract]
  type jsStyle = {
    default: ReactDOMRe.style,
    hover: ReactDOMRe.style,
    pressed: ReactDOMRe.style,
  };
  [@bs.deriving abstract]
  type jsGeography = {id: string};
  [@bs.deriving abstract]
  type jsProps = {
    geography: jsGeography,
    projection: string,
    style: jsStyle,
  };
  let make = (~geography, ~projection, ~style, children) =>
    ReasonReact.wrapJsForReason(
      ~reactClass=geographyComponent,
      ~props=jsProps(~geography, ~projection, ~style),
      children,
    );
};

module Markers = {
  [@bs.module "react-simple-maps"]
  external markersComponent : ReasonReact.reactClass = "Markers";
  let make = children =>
    ReasonReact.wrapJsForReason(
      ~reactClass=markersComponent,
      ~props=(),
      children,
    );
};

module Marker = {
  [@bs.module "react-simple-maps"]
  external markerComponent : ReasonReact.reactClass = "Marker";
  [@bs.deriving abstract]
  type jsStyle = {
    default: ReactDOMRe.style,
    hover: ReactDOMRe.style,
    pressed: ReactDOMRe.style,
  };
  [@bs.deriving abstract]
  type jsMarker = {
    coordinates: array(float),
    markerOffset: int,
    name: string,
  };
  [@bs.deriving abstract]
  type jsProps = {
    marker: jsMarker,
    tabable: bool,
    preserveMarkerAspect: bool,
    style: jsStyle,
  };
  let make = (~marker, ~tabable, ~preserveMarkerAspect, ~style, children) =>
    ReasonReact.wrapJsForReason(
      ~reactClass=markerComponent,
      ~props=jsProps(~marker, ~tabable, ~preserveMarkerAspect, ~style),
      children,
    );
};