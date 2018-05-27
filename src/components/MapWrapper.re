open SimpleMap;

/* State declaration */
type state = {markers: array(Marker.jsMarker)};

/* Action declaration */
type action =
  | Fetch(array(Marker.jsMarker));

let component = ReasonReact.reducerComponent("MapWrapper");

/* underscores before names indicate unused variables. We name them for clarity */
let make = _children => {
  ...component,
  didMount: self => {
    Fetcher.fetchPost(
      ~url="https://immense-river-25513.herokuapp.com/add-location",
      ~body="kthorri",
    );
    Fetcher.fetchPost(
      ~url="https://immense-river-25513.herokuapp.com/add-location",
      ~body="IronPeak",
    );
    Fetcher.fetchPost(
      ~url="https://immense-river-25513.herokuapp.com/add-location",
      ~body="Freysi21",
    );
    Fetcher.fetchGet(
      ~url="https://immense-river-25513.herokuapp.com/locations", ~cb=data =>
      self.send(
        Fetch(
          Array.map(
            stuff => {
              let (lat, long) = Fetcher.location(stuff);
              Marker.jsMarker(
                ~name=Fetcher.username(stuff),
                ~markerOffset=-25,
                ~coordinates=[|long, lat|],
              );
            },
            data,
          ),
        ),
      )
    );
  },
  initialState: () => {markers: [||]},
  /* State transitions */
  reducer: (action, _state) =>
    switch (action) {
    | Fetch(data) => ReasonReact.Update({markers: data})
    },
  render: self =>
    Array.length(self.state.markers) > 0 ?
      <div>
        <ComposableMap
          width=1600
          height=900
          projection="times"
          projectionConfig=(
            ComposableMap.projectionconfig(
              ~scale=205,
              ~rotation=[|(-11), 0, 0|],
            )
          )>
          <ZoomableGroup center=[|0, 20|] disablePanning=false>
            <Geographies
              geography="../../world-50m.json" disableOptimization=false>
              ...(
                   (geographies, projection) =>
                     Array.mapi(
                       (index, geography) =>
                         <Geography
                           key=(string_of_int(index))
                           geography
                           projection
                           style=(
                             Geography.jsStyle(
                               ~default=
                                 ReactDOMRe.Style.make(
                                   ~fill="#ECEFF1",
                                   ~stroke="#607D8B",
                                   ~strokeWidth="0.75",
                                   ~outline="none",
                                   (),
                                 ),
                               ~hover=
                                 ReactDOMRe.Style.make(
                                   ~fill="#607D8B",
                                   ~stroke="#607D8B",
                                   ~strokeWidth="0.75",
                                   ~outline="none",
                                   (),
                                 ),
                               ~pressed=
                                 ReactDOMRe.Style.make(
                                   ~fill="#FF5722",
                                   ~stroke="#607D8B",
                                   ~strokeWidth="0.75",
                                   ~outline="none",
                                   (),
                                 ),
                             )
                           )
                         />,
                       geographies,
                     )
                 )
            </Geographies>
            <Markers>
              ...(
                   Array.mapi(
                     (index, marker) =>
                       <Marker
                         key=(string_of_int(index))
                         marker
                         tabable=false
                         preserveMarkerAspect=false
                         style=(
                           Marker.jsStyle(
                             ~default=
                               ReactDOMRe.Style.make(~fill="#FF5722", ()),
                             ~hover=
                               ReactDOMRe.Style.make(~fill="#FFFFFF", ()),
                             ~pressed=
                               ReactDOMRe.Style.make(~fill="#FF5722", ()),
                           )
                         )>
                         <circle
                           cx="0"
                           cy="0"
                           r="6px"
                           style=(
                             ReactDOMRe.Style.make(
                               ~stroke="#FF5722",
                               ~strokeWidth="3px",
                               ~opacity="0.9",
                               (),
                             )
                           )
                         />
                         <text
                           textAnchor="middle"
                           y=(string_of_int(Marker.markerOffset(marker)))
                           style=(
                             ReactDOMRe.Style.make(
                               ~fontFamily="Roboto, sans-serif",
                               ~fill="#607D8B",
                               (),
                             )
                           )>
                           (ReasonReact.string(Marker.name(marker)))
                         </text>
                       </Marker>,
                     self.state.markers,
                   )
                 )
            </Markers>
          </ZoomableGroup>
        </ComposableMap>
      </div> :
      <div> (ReasonReact.string("Loading")) </div>,
};