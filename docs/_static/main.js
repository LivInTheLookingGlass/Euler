$(document).ready(function() {
    $('table.datatable').DataTable({
        autoWidth: false,
        paging: false,
        responsive: true,
        scrollX: false,
        searching: false,
    });
});

$(window).on('resize', function() {
    $('table.datatable').DataTable().columns.adjust().draw();
});
